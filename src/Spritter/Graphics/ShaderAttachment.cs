using grabs.ShaderCompiler;

namespace Spritter.Graphics;

public struct ShaderAttachment(ShaderStage stage, byte[] spirv, string entryPoint)
{
    public readonly ShaderStage Stage = stage;

    public readonly byte[] Spirv = spirv;

    public readonly string EntryPoint = entryPoint;

    public static ShaderAttachment FromHLSL(ShaderStage stage, string hlsl, string entryPoint)
    { 
#if DEBUG
        const bool debug = true;
#else
        const bool debug = false;
#endif

        byte[] spirv = Compiler.CompileHlsl(stage.ToGrabs(), hlsl, entryPoint, debug);

        return new ShaderAttachment(stage, spirv, entryPoint);
    }
}