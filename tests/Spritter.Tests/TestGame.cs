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
    
    private Shader _shader;

    public TestGame(in GameOptions options) : base(in options)
    {
        _shader = GraphicsDevice.CreateShader(
            ShaderAttachment.FromHLSL(ShaderStage.Vertex, ShaderCode, "VSMain"),
            ShaderAttachment.FromHLSL(ShaderStage.Pixel, ShaderCode, "PSMain")
        );
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
    }

    public override void Dispose()
    {
        _shader.Dispose();
        
        base.Dispose();
    }
}