using System.Drawing;
using Silk.NET.OpenGL;

namespace Spritter.Graphics.OpenGL;

internal sealed unsafe class GLTexture : Texture
{
    private readonly GL _gl;

    public readonly uint Texture;

    public GLTexture(GL gl, ReadOnlySpan<byte> data, Size size, PixelFormat format)
    {
        _gl = gl;
        
        Texture = _gl.GenTexture();
        _gl.BindTexture(TextureTarget.Texture2D, Texture);

        (InternalFormat iFmt, Silk.NET.OpenGL.PixelFormat pFmt, PixelType type) = format switch
        {
            PixelFormat.RGBA8 => (InternalFormat.Rgba, Silk.NET.OpenGL.PixelFormat.Rgba, PixelType.UnsignedByte),
            _ => throw new ArgumentOutOfRangeException(nameof(format), format, null)
        };

        fixed (void* pData = data)
        {
            _gl.TexImage2D(TextureTarget.Texture2D, 0, iFmt, (uint) size.Width, (uint) size.Height, 0, pFmt, type,
                pData);
        }
        
        _gl.GenerateMipmap(TextureTarget.Texture2D);
    }
    
    public override void Dispose()
    {
        _gl.DeleteTexture(Texture);
    }
}