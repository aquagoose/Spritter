namespace Spritter.Graphics;

public struct ShaderAttachment
{
    public ShaderStage Stage;

    public string Code;

    public string EntryPoint;

    public ShaderAttachment(ShaderStage stage, string code, string entryPoint)
    {
        Stage = stage;
        Code = code;
        EntryPoint = entryPoint;
    }
}