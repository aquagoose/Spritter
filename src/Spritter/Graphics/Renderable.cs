using grabs.Graphics;
using Buffer = grabs.Graphics.Buffer;

namespace Spritter.Graphics;

public class Renderable : IDisposable
{
    private readonly GraphicsDevice _gd;
    
    private readonly Buffer _vertexBuffer;
    private readonly Buffer _indexBuffer;

    private readonly Shader _shader;

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
            PipelineInfo pipelineInfo = new()
            {
                VertexShader = _shader.ShaderModules[ShaderStage.Vertex],
                PixelShader = _shader.ShaderModules[ShaderStage.Pixel],
                
                ColorAttachmentFormats = [_gd.CurrentState.RenderPassFormat],
                
            }
        }

        return pipeline;
    }

    private record struct RenderableState
    {
        public GraphicsState GraphicsState;
    }
}