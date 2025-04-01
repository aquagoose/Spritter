namespace Spritter.Graphics;

public struct ShaderAttachment(ShaderStage stage, byte[] spirv)
{
    public readonly ShaderStage Stage = stage;

    public readonly byte[] Spirv = spirv;

    public static ShaderAttachment FromHLSL(ShaderStage stage, string hlsl, string entryPoint)
    {
        
    }
}