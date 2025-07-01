namespace Spritter.Graphics;

public abstract class Renderable : IDisposable
{
    public abstract void Update<TVertex>(in ReadOnlySpan<TVertex> vertices, in ReadOnlySpan<uint> indices)
        where TVertex : unmanaged;

    public abstract void PushUniform<T>(string name, T data) where T : unmanaged;

    public abstract void PushTexture(string name, Texture texture);
    
    public abstract void Draw(uint numIndices);
    
    public abstract void Dispose();
}