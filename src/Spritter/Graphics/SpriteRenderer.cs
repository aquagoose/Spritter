using System.Diagnostics;
using System.Drawing;
using System.Numerics;
using Spritter.Graphics.Structs;

namespace Spritter.Graphics;

public class SpriteRenderer : IDisposable
{
    public const uint MaxSprites = 4096;

    private const uint NumVertices = 4;
    private const uint NumIndices = 6;

    private const uint MaxVertices = MaxSprites * NumVertices;
    private const uint MaxIndices = MaxSprites * NumIndices;
    
    private readonly Vertex[] _vertices;
    private readonly uint[] _indices;
    
    private readonly Shader _shader;
    private readonly Renderable _renderable;

    private readonly List<DrawItem> _drawQueue;
    
    public SpriteRenderer(GraphicsDevice device)
    {
        _vertices = new Vertex[MaxVertices];
        _indices = new uint[MaxIndices];
        
        _shader = device.CreateShader(
            ShaderAttachment.FromHLSL(ShaderStage.Vertex, ShaderCode, "VSMain"),
            ShaderAttachment.FromHLSL(ShaderStage.Pixel, ShaderCode, "PSMain")
        );

        RenderableInfo renderableInfo = new()
        {
            Vertices = GraphicsUtils.EmptySpan<Vertex>(MaxVertices),
            Indices = GraphicsUtils.EmptySpan<uint>(MaxIndices),
            Shader = _shader,
            ShaderStride = Vertex.SizeInBytes,
            ShaderLayout =
            [
                new ShaderAttribute(AttributeType.Float2, 0), 
                new ShaderAttribute(AttributeType.Float2, 8),
                new ShaderAttribute(AttributeType.Norm4, 16)
            ],
            Uniforms =
            [
                new ShaderUniform(UniformType.ConstantBuffer, 0, CameraMatrices.SizeInBytes),
                new ShaderUniform(UniformType.Texture, 1)
            ],
            Dynamic = true
        };

        _renderable = device.CreateRenderable(in renderableInfo);

        _drawQueue = new List<DrawItem>();
    }

    public void Draw(Texture texture, in Vector2 topLeft, in Vector2 topRight, in Vector2 bottomLeft,
        in Vector2 bottomRight, Color tint)
    {
        _drawQueue.Add(new DrawItem(texture, topLeft, topRight, bottomLeft, bottomRight, null, tint));
    }

    public void Render(Matrix4x4? transform = null, Matrix4x4? projection = null)
    {
        CameraMatrices matrices = new()
        {
            Projection = projection ?? Matrix4x4.CreateOrthographicOffCenter(0, 1280, 720, 0, -1, 1),
            View = transform ?? Matrix4x4.Identity
        };
        
        _renderable.PushUniformData(0, matrices);

        uint numDraws = 0;
        Texture? texture = null;
        foreach (DrawItem item in _drawQueue)
        {
            if (numDraws >= MaxSprites || item.Texture != texture)
            {
                Flush(numDraws, texture);
                numDraws = 0;
            }

            texture = item.Texture;

            uint vOffset = numDraws * NumVertices;
            uint iOffset = numDraws * NumIndices;

            Color tint = item.Tint;
            uint packedTint = (uint) ((tint.R << 24) | (tint.G << 16) | (tint.B << 8) | tint.A);

            _vertices[vOffset + 0] = new Vertex(item.TopLeft, new Vector2(0, 0), packedTint);
            _vertices[vOffset + 1] = new Vertex(item.TopRight, new Vector2(1, 0), packedTint);
            _vertices[vOffset + 2] = new Vertex(item.BottomRight, new Vector2(1, 1), packedTint);
            _vertices[vOffset + 3] = new Vertex(item.BottomLeft, new Vector2(0, 1), packedTint);

            _indices[iOffset + 0] = 0 + vOffset;
            _indices[iOffset + 1] = 1 + vOffset;
            _indices[iOffset + 2] = 3 + vOffset;
            _indices[iOffset + 3] = 1 + vOffset;
            _indices[iOffset + 4] = 2 + vOffset;
            _indices[iOffset + 5] = 3 + vOffset;

            numDraws++;
        }
        
        Flush(numDraws, texture);
        _drawQueue.Clear();
    }

    private void Flush(uint numDraws, Texture? texture)
    {
        if (numDraws == 0 || texture == null)
            return;

        _renderable.UpdateVertices<Vertex>(_vertices.AsSpan().Slice(0, (int) (numDraws * NumVertices)));
        _renderable.UpdateIndices<uint>(_indices.AsSpan().Slice(0, (int) (numDraws * NumIndices)));
        
        _renderable.PushTexture(1, texture);
        
        _renderable.Draw(numDraws * NumIndices, IndexFormat.UInt);
    }

    public void Dispose()
    {
        _renderable.Dispose();
        _shader.Dispose();
    }

    private readonly struct DrawItem(
        Texture texture,
        Vector2 topLeft,
        Vector2 topRight,
        Vector2 bottomLeft,
        Vector2 bottomRight,
        Rectangle? source,
        Color tint)
    {
        public readonly Texture Texture = texture;
        public readonly Vector2 TopLeft = topLeft;
        public readonly Vector2 TopRight = topRight;
        public readonly Vector2 BottomLeft = bottomLeft;
        public readonly Vector2 BottomRight = bottomRight;
        public readonly Rectangle? Source = source;
        public readonly Color Tint = tint;
    }

    private readonly struct Vertex
    {
        public const uint SizeInBytes = 20;
        
        public readonly Vector2 Position;
        public readonly Vector2 TexCoord;
        public readonly uint RgbaTint;

        public Vertex(Vector2 position, Vector2 texCoord, uint rgbaTint)
        {
            Position = position;
            TexCoord = texCoord;
            RgbaTint = rgbaTint;
        }
    }

    private const string ShaderCode = @"
struct VSInput
{
    float2 Position: POSITION0;
    float2 TexCoord: TEXCOORD0;
    float4 Tint:     COLOR0;
};

struct VSOutput
{
    float4 Position: SV_Position;
    float2 TexCoord: TEXCOORD0;
    float4 Tint:     COLOR0;
};

struct PSOutput
{
    float4 Color: SV_Target0;
};

cbuffer Matrices : register(b0)
{
    float4x4 Projection;
    float4x4 Transform;
}

Texture2D Sprite   : register(t1);
SamplerState State : register(s1);

VSOutput VSMain(const in VSInput input)
{
    VSOutput output;

    output.Position = mul(Projection, mul(Transform, float4(input.Position, 0.0, 1.0)));
    output.TexCoord = input.TexCoord;
    output.Tint = input.Tint;

    return output;
}

PSOutput PSMain(const in VSOutput input)
{
    PSOutput output;

    output.Color = Sprite.Sample(State, input.TexCoord) * input.Tint;

    return output;
}
";
}