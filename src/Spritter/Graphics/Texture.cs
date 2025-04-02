global using GrabsTexture = grabs.Graphics.Texture;
using System.Drawing;
using grabs.Core;
using grabs.Graphics;

namespace Spritter.Graphics;

public class Texture : IDisposable
{
    internal GrabsTexture GrabsTexture;

    internal Texture(Device device, Size size, ref readonly ReadOnlySpan<byte> data, PixelFormat format)
    {
        Format fmt = format switch
        {
            PixelFormat.R8G8B8A8_UNorm => Format.R8G8B8A8_UNorm,
            _ => throw new ArgumentOutOfRangeException(nameof(format), format, null)
        };

        TextureInfo info =
            TextureInfo.Texture2D(new Size2D((uint) size.Width, (uint) size.Height), fmt, TextureUsage.Sampled);

        GrabsTexture = device.CreateTexture(in info, in data);
    }
    
    public void Dispose()
    {
        GrabsTexture.Dispose();
    }
}