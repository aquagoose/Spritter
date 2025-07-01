namespace Spritter.Graphics;

public ref struct RenderableInfo
{
    /// <summary>
    /// The number of vertices in the vertex buffer.
    /// </summary>
    /// <remarks>This is multiplied by <see cref="VertexSize"/> to get the size in bytes.</remarks>
    public uint NumVertices;

    /// <summary>
    /// The number of indices in the index buffer.
    /// </summary>
    /// <remarks>This is multiplied by the size of a single index, which is a uint, to get the size in bytes.</remarks>
    public uint NumIndices;

    /// <summary>
    /// The <see cref="Spritter.Graphics.Shader"/> to use.
    /// </summary>
    public Shader Shader;

    /// <summary>
    /// The field layout of a single vertex.
    /// </summary>
    public ReadOnlySpan<VertexElement> VertexLayout;
    
    /// <summary>
    /// The size in bytes of a single vertex.
    /// </summary>
    public uint VertexSize;

    /// <summary>
    /// The uniforms present in the shader.
    /// </summary>
    public ReadOnlySpan<Uniform> Uniforms;

    /// <summary>
    /// Enable if the renderable will be updated often.
    /// </summary>
    public bool Dynamic;
}