namespace Spritter.Graphics;

public record struct ShaderUniform(UniformType Type, uint BindPoint, uint BufferSize = 0)
{
    public UniformType Type = Type;
    
    public uint BindPoint = BindPoint;
    
    public uint BufferSize = BufferSize;
}