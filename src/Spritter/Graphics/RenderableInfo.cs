namespace Spritter.Graphics;

public ref struct RenderableInfo(
    ReadOnlySpan<byte> vertices,
    ReadOnlySpan<byte> indices,
    Shader shader,
    uint shaderStride,
    ReadOnlySpan<ShaderAttribute> shaderLayout,
    ReadOnlySpan<ShaderUniform> uniforms,
    bool dynamic)
{
    public ReadOnlySpan<byte> Vertices = vertices;

    public ReadOnlySpan<byte> Indices = indices;

    public Shader Shader = shader;

    public uint ShaderStride = shaderStride;

    public ReadOnlySpan<ShaderAttribute> ShaderLayout = shaderLayout;

    public ReadOnlySpan<ShaderUniform> Uniforms = uniforms;

    public bool Dynamic = dynamic;
}