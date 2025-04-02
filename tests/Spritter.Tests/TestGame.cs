using System.Drawing;
using System.Numerics;
using Spritter.Graphics;

namespace Spritter.Tests;

public class TestGame : Game
{
    private const string ShaderCode = @"
struct VSInput
{
    float2 Position: POSITION0;
    float2 TexCoord: TEXCOORD0;
};

struct VSOutput
{
    float4 Position: SV_Position;
    float2 TexCoord: TEXCOORD0;
};

struct PSOutput
{
    float4 Color: SV_Target0;
};

cbuffer TransformMatrix : register(b0)
{
    float4x4 Transform;
}

Texture2D Texture : register(t1);
SamplerState State : register(s1);

VSOutput VSMain(const in VSInput input)
{
    VSOutput output;

    output.Position = mul(Transform, float4(input.Position, 0.0, 1.0));
    output.TexCoord = input.TexCoord;

    return output;
}

PSOutput PSMain(const in VSOutput input)
{
    PSOutput output;

    output.Color = Texture.Sample(State, input.TexCoord);

    return output;
}
";
    
    private readonly Shader _shader;
    private readonly Renderable _renderable;
    private readonly Texture _texture;

    public TestGame(in GameOptions options) : base(in options)
    {
        _shader = GraphicsDevice.CreateShader(
            ShaderAttachment.FromHLSL(ShaderStage.Vertex, ShaderCode, "VSMain"),
            ShaderAttachment.FromHLSL(ShaderStage.Pixel, ShaderCode, "PSMain")
        );
        
        Span<float> vertices = 
        [
            -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, +0.5f, 0.0f, 1.0f,
            +0.5f, +0.5f, 1.0f, 1.0f,
            +0.5f, -0.5f, 1.0f, 0.0f
        ];

        Span<uint> indices =
        [
            0, 1, 3,
            1, 2, 3
        ];

        RenderableInfo info = new()
        {
            Vertices = vertices,
            Indices = indices,
            Shader = _shader,
            ShaderLayout = [new ShaderAttribute(AttributeType.Float2, 0), new ShaderAttribute(AttributeType.Float2, 8)],
            ShaderStride = 4 * sizeof(float),
            Uniforms = [new ShaderUniform(UniformType.ConstantBuffer, 0, 64), new ShaderUniform(UniformType.Texture, 1, 0)]
        };

        _renderable = GraphicsDevice.CreateRenderable(in info);

        _texture = GraphicsDevice.CreateTexture("/home/aqua/Pictures/BAGELMIP.png");
    }

    private float _value;

    protected override void Update(float dt)
    {
        base.Update(dt);

        _value += dt;
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
        
        _renderable.PushUniformData(0, Matrix4x4.CreateRotationZ(_value));
        _renderable.PushTextureData(1, _texture);
        _renderable.Draw(6);
        
        _renderable.PushUniformData(0, Matrix4x4.CreateRotationZ(-_value));
        _renderable.Draw(6);
    }

    public override void Dispose()
    {
        _texture.Dispose();
        _renderable.Dispose();
        _shader.Dispose();
        
        base.Dispose();
    }
}