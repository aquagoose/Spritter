using grabs.Graphics;

namespace Spritter.Graphics;

public class Shader : IDisposable
{
    internal Dictionary<ShaderStage, ShaderModule> ShaderModules;
    
    internal Shader(Device device, ref readonly ReadOnlySpan<ShaderAttachment> attachments)
    {
        ShaderModules = new Dictionary<ShaderStage, ShaderModule>();

        foreach (ShaderAttachment attachment in attachments)
        {
            ShaderModule module =
                device.CreateShaderModule(attachment.Stage.ToGrabs(), attachment.Spirv, attachment.EntryPoint);
            
            ShaderModules.Add(attachment.Stage, module);
        }
    }
    
    public void Dispose()
    {
        foreach ((_, ShaderModule module) in ShaderModules)
            module.Dispose();
    }
}