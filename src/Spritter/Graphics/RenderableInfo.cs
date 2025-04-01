namespace Spritter.Graphics;

public ref struct RenderableInfo(ReadOnlySpan<float> vertices, ReadOnlySpan<uint> indices, Shader shader, uint shaderStride, ReadOnlySpan<ShaderAttribute> shaderLayout)
{
    public ReadOnlySpan<float> Vertices = vertices;

    public ReadOnlySpan<uint> Indices = indices;

    public Shader Shader = shader;

    public uint ShaderStride = shaderStride;

    public ReadOnlySpan<ShaderAttribute> ShaderLayout = shaderLayout;
}