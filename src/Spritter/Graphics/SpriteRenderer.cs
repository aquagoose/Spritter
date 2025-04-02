namespace Spritter.Graphics;

public class SpriteRenderer : IDisposable
{
    private readonly Shader _shader;
    
    public SpriteRenderer(GraphicsDevice device)
    {
        _shader = device.CreateShader(
            ShaderAttachment.FromHLSL(ShaderStage.Vertex, ShaderCode, "VSMain"),
            ShaderAttachment.FromHLSL(ShaderStage.Pixel, ShaderCode, "PSMain")
        );
        
        RenderableInfo renderableInfo = new()
        {
            
        }
    }

    public void Dispose()
    {
        _shader.Dispose();
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