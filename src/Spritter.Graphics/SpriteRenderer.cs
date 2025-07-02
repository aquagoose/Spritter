using System.Diagnostics;
using System.Drawing;
using System.Numerics;

namespace Spritter.Graphics;

public class SpriteRenderer : IDisposable
{
    private const uint MaxSprites = 4096;
    
    private const uint NumVertices = 4;
    private const uint NumIndices = 6;
    
    private readonly List<DrawCommand> _drawList;
    
    private readonly Vertex[] _vertices;
    private readonly uint[] _indices;

    private readonly Shader _shader;
    private readonly Renderable _renderable;

    public SpriteRenderer(GraphicsDevice device)
    {
        _drawList = [];
        
        _vertices = new Vertex[MaxSprites * NumVertices];
        _indices = new uint[MaxSprites * NumIndices];

        _shader = device.CreateShader(new ShaderAttachment(ShaderStage.Vertex, VertexShader, "main"),
            new ShaderAttachment(ShaderStage.Pixel, PixelShader, "main"));

        RenderableInfo info = new()
        {
            NumVertices = (uint) _vertices.Length,
            NumIndices = (uint) _indices.Length,
            Shader = _shader,
            VertexSize = Vertex.SizeInBytes,
            VertexLayout =
            [
                new VertexElement("aPosition", VertexElementType.Float2, 0),
                new VertexElement("aTexCoord", VertexElementType.Float2, 8),
                new VertexElement("aTint", VertexElementType.NByte4, 16)
            ],
            Uniforms =
            [
                new Uniform(UniformType.ConstantBuffer, "Matrices", Matrices.SizeInBytes),
                new Uniform(UniformType.Texture, "uTexture")
            ]
        };

        _renderable = device.CreateRenderable(in info);
    }

    public void Draw(Texture texture, Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight, Color tint)
    {
        _drawList.Add(new DrawCommand(texture, topLeft, topRight, bottomLeft, bottomRight, tint));
    }

    public void Render(Matrix4x4? transform = null, Matrix4x4? projection = null)
    {
        Matrices matrices = new()
        {
            Projection = projection ?? Matrix4x4.CreateOrthographicOffCenter(0, 1280, 720, 0, -1, 1),
            Transform = transform ?? Matrix4x4.Identity
        };
        _renderable.PushUniform("Matrices", matrices);

        uint numDraws = 0;
        Texture? currentTexture = null;
        foreach (DrawCommand cmd in _drawList)
        {
            if (cmd.Texture != currentTexture || numDraws >= MaxSprites)
                Flush(currentTexture, numDraws);

            currentTexture = cmd.Texture;

            uint tint = (uint) ((cmd.Tint.R << 24) | (cmd.Tint.G << 16) | (cmd.Tint.B << 8) | cmd.Tint.A);
            
            uint vOffset = numDraws * NumVertices;
            uint iOffset = numDraws * NumIndices;

            _vertices[vOffset + 0] = new Vertex(cmd.TopLeft, new Vector2(0, 0), tint);
            _vertices[vOffset + 1] = new Vertex(cmd.TopRight, new Vector2(1, 0), tint);
            _vertices[vOffset + 2] = new Vertex(cmd.BottomRight, new Vector2(1, 1), tint);
            _vertices[vOffset + 3] = new Vertex(cmd.BottomLeft, new Vector2(0, 1), tint);

            _indices[iOffset + 0] = 0 + vOffset;
            _indices[iOffset + 1] = 1 + vOffset;
            _indices[iOffset + 2] = 3 + vOffset;
            _indices[iOffset + 3] = 1 + vOffset;
            _indices[iOffset + 4] = 2 + vOffset;
            _indices[iOffset + 5] = 3 + vOffset;

            numDraws++;
        }
        
        Flush(currentTexture, numDraws);
        
        _drawList.Clear();
    }

    private void Flush(Texture? texture, uint numDraws)
    {
        if (numDraws == 0)
            return;
        
        Debug.Assert(texture != null);

        _renderable.Update<Vertex>(_vertices.AsSpan(0, (int) (numDraws * NumVertices)),
            _indices.AsSpan(0, (int) (numDraws * NumIndices)));
        
        _renderable.PushTexture("uTexture", texture);
        _renderable.Draw(numDraws * NumIndices);
    }
    
    public void Dispose()
    {
        _renderable.Dispose();
        _shader.Dispose();
    }

    private readonly struct DrawCommand
    {
        public readonly Texture Texture;
        public readonly Vector2 TopLeft;
        public readonly Vector2 TopRight;
        public readonly Vector2 BottomLeft;
        public readonly Vector2 BottomRight;
        public readonly Color Tint;

        public DrawCommand(Texture texture, Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight, Color tint)
        {
            Texture = texture;
            TopLeft = topLeft;
            TopRight = topRight;
            BottomLeft = bottomLeft;
            BottomRight = bottomRight;
            Tint = tint;
        }
    }
    
    private readonly struct Vertex
    {
        public const uint SizeInBytes = 20;
        
        public readonly Vector2 Position;
        public readonly Vector2 TexCoord;
        public readonly uint Tint;

        public Vertex(Vector2 position, Vector2 texCoord, uint tint)
        {
            Position = position;
            TexCoord = texCoord;
            Tint = tint;
        }
    }

    private struct Matrices
    {
        public const uint SizeInBytes = 128;
        
        public Matrix4x4 Projection;
        public Matrix4x4 Transform;
    }

    private const string VertexShader = """
                                        #version 330 core

                                        in vec2 aPosition;
                                        in vec2 aTexCoord;
                                        in vec4 aTint;

                                        out vec2 frag_TexCoord;
                                        out vec4 frag_Tint;

                                        layout (std140) uniform Matrices
                                        {
                                            mat4 uProjection;
                                            mat4 uTransform;
                                        };

                                        void main()
                                        {
                                            gl_Position = uProjection * uTransform * vec4(aPosition, 0.0, 1.0);
                                            frag_TexCoord = aTexCoord;
                                            frag_Tint = aTint;
                                        }
                                        """;

    private const string PixelShader = """
                                       #version 330 core

                                       in vec2 frag_TexCoord;
                                       in vec4 frag_Tint;

                                       out vec4 out_Tint;

                                       uniform sampler2D uTexture;

                                       void main()
                                       {
                                           out_Tint = texture(uTexture, frag_TexCoord) * frag_Tint;
                                       }
                                       """;
}