using System.Drawing;
using Spritter.Graphics.OpenGL;
using StbImageSharp;

namespace Spritter.Graphics;

public abstract class GraphicsDevice : IDisposable
{
    public abstract Shader CreateShader(params ReadOnlySpan<ShaderAttachment> attachments);

    public abstract Renderable CreateRenderable(in RenderableInfo info);

    public abstract Texture CreateTexture(byte[] data, Size size, PixelFormat format = PixelFormat.RGBA8);

    public Texture CreateTexture(string path)
    {
        using FileStream stream = File.OpenRead(path);
        ImageResult result = ImageResult.FromStream(stream, ColorComponents.RedGreenBlueAlpha);
        return CreateTexture(result.Data, new Size(result.Width, result.Height), PixelFormat.RGBA8);
    }
    
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