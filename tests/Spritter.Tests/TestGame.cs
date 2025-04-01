using System.Drawing;
using Spritter.Graphics;

namespace Spritter.Tests;

public class TestGame : Game
{
    private const string ShaderCode = @"
struct VSInput
{
    float2 Position: POSITION0;
    float3 Color:    COLOR0;
};

struct VSOutput
{
    float4 Position: SV_Position;
    float3 Color:    COLOR0;
};

struct PSOutput
{
    float4 Color: SV_Target0;
};

VSOutput VSMain(const in VSInput input)
{
    VSOutput output;

    output.Position = float4(input.Position, 0.0, 1.0);
    output.Color = input.Color;

    return output;
}

PSOutput PSMain(const in VSOutput input)
{
    PSOutput output;

    output.Color = float4(input.Color, 1.0);

    return output;
}
";
    
    private readonly Shader _shader;
    private readonly Renderable _renderable;

    public TestGame(in GameOptions options) : base(in options)
    {
        _shader = GraphicsDevice.CreateShader(
            ShaderAttachment.FromHLSL(ShaderStage.Vertex, ShaderCode, "VSMain"),
            ShaderAttachment.FromHLSL(ShaderStage.Pixel, ShaderCode, "PSMain")
        );
        
        Span<float> vertices = 
        [
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, +0.5f, 0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, 0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, 0.0f, 0.0f, 0.0f
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
            ShaderLayout = [new ShaderAttribute(AttributeType.Float2, 0), new ShaderAttribute(AttributeType.Float3, 8)],
            ShaderStride = 5 * sizeof(float)
        };

        _renderable = GraphicsDevice.CreateRenderable(in info);
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
        
        _renderable.Draw(6);
    }

    public override void Dispose()
    {
        _renderable.Dispose();
        _shader.Dispose();
        
        base.Dispose();
    }
}