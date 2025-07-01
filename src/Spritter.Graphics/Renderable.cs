namespace Spritter.Graphics;

public abstract class Renderable : IDisposable
{
    public abstract void Update<TVertex>(in ReadOnlySpan<TVertex> vertices, in ReadOnlySpan<uint> indices)
        where TVertex : unmanaged;
    
    public abstract void Draw(uint numIndices);
    
    public abstract void Dispose();
}