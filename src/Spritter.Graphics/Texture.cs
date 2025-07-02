using System.Drawing;

namespace Spritter.Graphics;

public abstract class Texture : IDisposable
{
    public readonly Size Size;

    protected Texture(Size size)
    {
        Size = size;
    }
    
    public abstract void Dispose();
}