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
    
    private RenderableState _currentState;
    private Dictionary<RenderableState, Pipeline> _pipelineStates;
    
    internal Renderable(GraphicsDevice gd, ref readonly RenderableInfo info)
    {
        _gd = gd;
        Device device = gd.Device;

        BufferUsage usage = 0;

        _vertexBuffer = device.CreateBuffer(usage | BufferUsage.Vertex, info.Vertices);
        _indexBuffer = device.CreateBuffer(usage | BufferUsage.Index, info.Indices);

        _shader = info.Shader;
        _stride = info.ShaderStride;

        _shaderLayout = info.ShaderLayout.ToArray();

        _pipelineStates = new Dictionary<RenderableState, Pipeline>();
    }

    public void Draw(uint numDraws)
    {
        CommandList cl = _gd.CommandList;

        Pipeline pipeline = GetOrCreatePipeline();
        
        cl.SetPipeline(pipeline);
        cl.SetVertexBuffer(0, _vertexBuffer, _stride);
        cl.SetIndexBuffer(_indexBuffer, Format.R32_UInt);
        
        cl.DrawIndexed(numDraws);
    }
    
    public void Dispose()
    {
        foreach ((_, Pipeline pipeline) in _pipelineStates)
            pipeline.Dispose();
        
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
                InputLayout = inputLayout
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