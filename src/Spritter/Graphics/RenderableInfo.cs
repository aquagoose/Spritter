using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Spritter.Graphics;

public ref struct RenderableInfo(ReadOnlySpan<float> vertices, ReadOnlySpan<uint> indices, Shader shader)
{
    public ReadOnlySpan<float> Vertices = vertices;

    public ReadOnlySpan<uint> Indices = indices;

    public Shader Shader = shader;

    public static RenderableInfo FromT<T>(ReadOnlySpan<T> vertices, ReadOnlySpan<uint> indices, Shader shader) where T : unmanaged
    {
        ReadOnlySpan<float> fVerts = MemoryMarshal.Cast<T, float>(vertices);
        return new RenderableInfo(fVerts, indices, shader);
    }
}