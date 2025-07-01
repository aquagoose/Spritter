using System.Drawing;
using Spritter.Graphics.OpenGL;

namespace Spritter.Graphics;

public abstract class GraphicsDevice : IDisposable
{
    public abstract Shader CreateShader(params ReadOnlySpan<ShaderAttachment> attachments);

    public abstract Renderable CreateRenderable(in RenderableInfo info);
    
    public abstract void Clear(Color color);
    
    public abstract void Present();
    
    public abstract void Dispose();

    public static GraphicsDevice Create(IntPtr sdlWindow, Renderer renderer)
    {
        return renderer switch
        {
            Renderer.D3D11 => throw new NotImplementedException(),
            Renderer.OpenGL => new GLGraphicsDevice(sdlWindow),
            _ => throw new ArgumentOutOfRangeException(nameof(renderer), renderer, null)
        };
    }
}