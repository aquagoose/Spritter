using System.Drawing;
using System.Numerics;

namespace Spritter.Graphics;

public class SpriteRenderer : IDisposable
{
    public const uint MaxSprites = 4096;

    private const uint NumVertices = 4;
    private const uint NumIndices = 6;

    private const uint MaxVertices = MaxSprites * NumVertices;
    private const uint MaxIndices = MaxSprites * NumIndices;
    
    private readonly Shader _shader;
    private readonly Renderable _renderable;

    private readonly Vertex[] _vertices;
    private readonly uint[] _indices;
    
    public SpriteRenderer(GraphicsDevice device)
    {
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
                new ShaderAttribute(AttributeType.Float2, 0), new ShaderAttribute(AttributeType.Float2, 8),
                new ShaderAttribute(AttributeType.Norm4, 16)
            ],
            Uniforms =
            [
                new ShaderUniform(UniformType.ConstantBuffer, 0, 128), new ShaderUniform(UniformType.Texture, 1)
            ],
            Dynamic = true
        };

        _renderable = device.CreateRenderable(in renderableInfo);
    }

    public void Dispose()
    {
        _renderable.Dispose();
        _shader.Dispose();
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