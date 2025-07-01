using System.Runtime.CompilerServices;
using Silk.NET.OpenGL;

namespace Spritter.Graphics.OpenGL;

internal sealed unsafe class GLRenderable : Renderable
{
    private readonly GL _gl;
    
    private readonly uint _vao;
    
    private readonly uint _vertexBuffer;
    private readonly uint _indexBuffer;

    private readonly GLShader _shader;

    private readonly Dictionary<string, (uint binding, uint buffer)> _uniforms;

    public GLRenderable(GL gl, ref readonly RenderableInfo info)
    {
        _gl = gl;

        _vao = _gl.GenVertexArray();
        _gl.BindVertexArray(_vao);

        BufferUsageARB usage = info.Dynamic ? BufferUsageARB.DynamicDraw : BufferUsageARB.StaticDraw;
        
        _vertexBuffer = _gl.GenBuffer();
        _gl.BindBuffer(BufferTargetARB.ArrayBuffer, _vertexBuffer);
        _gl.BufferData(BufferTargetARB.ArrayBuffer, info.NumVertices * info.VertexSize, null, usage);
        
        _indexBuffer = _gl.GenBuffer();
        _gl.BindBuffer(BufferTargetARB.ElementArrayBuffer, _indexBuffer);
        _gl.BufferData(BufferTargetARB.ElementArrayBuffer, info.NumIndices * sizeof(uint), null, usage);

        _shader = (GLShader) info.Shader;
        
        _gl.UseProgram(_shader.Program);

        foreach (VertexElement element in info.VertexLayout)
        {
            int location = _gl.GetAttribLocation(_shader.Program, element.Name);

            if (location < 0)
                throw new Exception($"Vertex element with name '{element.Name}' not found.");
            
            _gl.EnableVertexAttribArray((uint) location);

            switch (element.Type)
            {
                case VertexElementType.Float:
                    _gl.VertexAttribPointer((uint) location, 1, VertexAttribPointerType.Float, false, info.VertexSize,
                        (void*) element.ByteOffset);
                    break;
                case VertexElementType.Float2:
                    _gl.VertexAttribPointer((uint) location, 2, VertexAttribPointerType.Float, false, info.VertexSize,
                        (void*) element.ByteOffset);
                    break;
                case VertexElementType.Float3:
                    _gl.VertexAttribPointer((uint) location, 3, VertexAttribPointerType.Float, false, info.VertexSize,
                        (void*) element.ByteOffset);
                    break;
                case VertexElementType.Float4:
                    _gl.VertexAttribPointer((uint) location, 4, VertexAttribPointerType.Float, false, info.VertexSize,
                        (void*) element.ByteOffset);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        _uniforms = [];
        
        for (int i = 0; i < info.Uniforms.Length; i++)
        {
            ref readonly Uniform uniform = ref info.Uniforms[i];

            uint binding = (uint) i;
            
            uint location = _gl.GetUniformBlockIndex(_shader.Program, uniform.Name);
            _gl.UniformBlockBinding(_shader.Program, location, binding);

            uint buffer = _gl.GenBuffer();
            _gl.BindBuffer(BufferTargetARB.UniformBuffer, buffer);
            _gl.BufferData(BufferTargetARB.UniformBuffer, uniform.BufferSize, null, BufferUsageARB.DynamicDraw);
            
            _uniforms.Add(uniform.Name, (binding, buffer));
        }
    }

    public override void Update<TVertex>(in ReadOnlySpan<TVertex> vertices, in ReadOnlySpan<uint> indices)
    {
        _gl.BindVertexArray(_vao);
        
        fixed (void* pVertices = vertices)
            _gl.BufferSubData(BufferTargetARB.ArrayBuffer, 0, (nuint) (vertices.Length * sizeof(TVertex)), pVertices);
        
        fixed (void* pIndices = indices)
            _gl.BufferSubData(BufferTargetARB.ElementArrayBuffer, 0, (nuint) (indices.Length * sizeof(uint)), pIndices);
    }

    public override void PushUniform<T>(string name, T data)
    {
        (uint binding, uint buffer) = _uniforms[name];
        
        _gl.BindBufferBase(BufferTargetARB.UniformBuffer, binding, buffer);
        _gl.BufferSubData(BufferTargetARB.UniformBuffer, 0, (uint) sizeof(T), Unsafe.AsPointer(ref data));
        _gl.BindBuffer(BufferTargetARB.UniformBuffer, 0);
    }

    public override void Draw(uint numIndices)
    {
        _gl.BindVertexArray(_vao);
        _gl.UseProgram(_shader.Program);
        
        foreach ((_, (uint binding, uint buffer)) in _uniforms)
            _gl.BindBufferBase(BufferTargetARB.UniformBuffer, binding, buffer);
        
        _gl.DrawElements(PrimitiveType.Triangles, numIndices, DrawElementsType.UnsignedInt, (void*) 0);
    }

    public override void Dispose()
    {
        _gl.DeleteBuffer(_indexBuffer);
        _gl.DeleteBuffer(_vertexBuffer);
        _gl.DeleteVertexArray(_vao);
    }
}