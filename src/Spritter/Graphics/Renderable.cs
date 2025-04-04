using grabs.Graphics;
using Buffer = grabs.Graphics.Buffer;

namespace Spritter.Graphics;

public class Renderable : IDisposable
{
    private readonly GraphicsDevice _gd;
    
    private readonly Buffer _vertexBuffer;
    private readonly Buffer _indexBuffer;

    private readonly Shader _shader;
    
    private readonly ShaderAttribute[] _shaderLayout;
    private readonly uint _stride;
    
    private readonly ShaderUniform[] _uniforms;
    private readonly Dictionary<uint, Buffer> _constantBuffers;
    
    private readonly DescriptorLayout _descriptorLayout;
    
    private RenderableState _currentState;
    private Dictionary<RenderableState, Pipeline> _pipelineStates;
    
    internal Renderable(GraphicsDevice gd, ref readonly RenderableInfo info)
    {
        _gd = gd;
        Device device = gd.Device;

        BufferUsage usage = info.Dynamic ? BufferUsage.Dynamic : 0;

        _vertexBuffer = device.CreateBuffer(usage | BufferUsage.Vertex, info.Vertices);
        _indexBuffer = device.CreateBuffer(usage | BufferUsage.Index, info.Indices);

        _shader = info.Shader;

        _shaderLayout = info.ShaderLayout.ToArray();
        _stride = info.ShaderStride;
        
        _uniforms = info.Uniforms.ToArray();
        _constantBuffers = new Dictionary<uint, Buffer>();

        Span<DescriptorBinding> descriptorBindings = stackalloc DescriptorBinding[_uniforms.Length];

        int i = 0;
        foreach (ShaderUniform uniform in _uniforms)
        {
            DescriptorType type;
            
            switch (uniform.Type)
            {
                case UniformType.ConstantBuffer:
                {
                    _constantBuffers.Add(uniform.BindPoint,
                        device.CreateBuffer(new BufferInfo(BufferUsage.Constant | BufferUsage.Dynamic,
                            uniform.BufferSize)));

                    type = DescriptorType.ConstantBuffer;
                    
                    break;
                }

                case UniformType.Texture:
                {
                    type = DescriptorType.Texture;
                    break;
                }
                
                default:
                    throw new ArgumentOutOfRangeException();
            }

            descriptorBindings[i] = new DescriptorBinding((uint) i, type, grabs.Graphics.ShaderStage.VertexPixel);

            i++;
        }

        _descriptorLayout = device.CreateDescriptorLayout(new DescriptorLayoutInfo(descriptorBindings));
        
        _pipelineStates = new Dictionary<RenderableState, Pipeline>();
    }

    public void UpdateVertices<T>(in ReadOnlySpan<T> vertices) where T : unmanaged
    {
        CommandList cl = _gd.CommandList;
        cl.UpdateBuffer(_vertexBuffer, in vertices);
    }

    public void UpdateIndices<T>(in ReadOnlySpan<T> indices) where T : unmanaged
    {
        CommandList cl = _gd.CommandList;
        cl.UpdateBuffer(_indexBuffer, in indices);
    }

    public void PushUniformData<T>(uint bindPoint, in ReadOnlySpan<T> data) where T : unmanaged
    {
        CommandList cl = _gd.CommandList;
        
        cl.UpdateBuffer(_constantBuffers[bindPoint], in data);

        cl.PushDescriptor(0, GetOrCreatePipeline(),
            new Descriptor(bindPoint, DescriptorType.ConstantBuffer, buffer: _constantBuffers[bindPoint]));
    }

    public void PushUniformData<T>(uint bindPoint, T[] data) where T : unmanaged
        => PushUniformData<T>(bindPoint, data.AsSpan());

    public void PushUniformData<T>(uint bindPoint, T data) where T : unmanaged
        => PushUniformData(bindPoint, new ReadOnlySpan<T>(ref data));

    public void PushTexture(uint bindPoint, Texture texture)
    {
        CommandList cl = _gd.CommandList;
        cl.PushDescriptor(0, GetOrCreatePipeline(),
            new Descriptor(bindPoint, DescriptorType.Texture, texture: texture.GrabsTexture));
    }

    public void Draw(uint numDraws, IndexFormat format)
    {
        CommandList cl = _gd.CommandList;

        Pipeline pipeline = GetOrCreatePipeline();

        Format fmt = format switch
        {
            IndexFormat.UShort => Format.R16_UInt,
            IndexFormat.UInt => Format.R32_UInt,
            _ => throw new ArgumentOutOfRangeException(nameof(format), format, null)
        };
        
        cl.SetPipeline(pipeline);
        cl.SetVertexBuffer(0, _vertexBuffer, _stride);
        cl.SetIndexBuffer(_indexBuffer, fmt);
        
        cl.DrawIndexed(numDraws);
    }
    
    public void Dispose()
    {
        foreach ((_, Pipeline pipeline) in _pipelineStates)
            pipeline.Dispose();
     
        _descriptorLayout.Dispose();
        
        foreach ((_, Buffer buffer) in _constantBuffers)
            buffer.Dispose();
        
        _indexBuffer.Dispose();
        _vertexBuffer.Dispose();
    }

    private Pipeline GetOrCreatePipeline()
    {
        _currentState.GraphicsState = _gd.CurrentState;

        if (!_pipelineStates.TryGetValue(_currentState, out Pipeline pipeline))
        {
            Span<InputElement> inputLayout = stackalloc InputElement[_shaderLayout.Length];

            for (int i = 0; i < _shaderLayout.Length; i++)
            {
                ref readonly ShaderAttribute attrib = ref _shaderLayout[i];

                inputLayout[i] = new InputElement()
                {
                    Format = attrib.Type switch
                    {
                        AttributeType.Float => Format.R32_Float,
                        AttributeType.Float2 => Format.R32G32_Float,
                        AttributeType.Float3 => Format.R32G32B32_Float,
                        AttributeType.Float4 => Format.R32G32B32A32_Float,
                        AttributeType.Byte => Format.R8_UInt,
                        AttributeType.Byte2 => Format.R8G8_UInt,
                        AttributeType.Byte4 => Format.R8G8B8A8_UInt,
                        AttributeType.Norm => Format.R8_UNorm,
                        AttributeType.Norm2 => Format.R8G8_UNorm,
                        AttributeType.Norm4 => Format.R8G8B8A8_UNorm,
                        _ => throw new ArgumentOutOfRangeException()
                    },
                    Offset = attrib.ByteOffset,
                    Slot = 0
                };
            }

            PipelineInfo pipelineInfo = new()
            {
                VertexShader = _shader.ShaderModules[ShaderStage.Vertex],
                PixelShader = _shader.ShaderModules[ShaderStage.Pixel],

                ColorAttachmentFormats = [_gd.CurrentState.RenderPassFormat],
                InputLayout = inputLayout,
                Descriptors = [_descriptorLayout]
            };

            pipeline = _gd.Device.CreatePipeline(in pipelineInfo);
            _pipelineStates.Add(_currentState, pipeline);
        }

        return pipeline;
    }

    private record struct RenderableState
    {
        public GraphicsState GraphicsState;
    }
}