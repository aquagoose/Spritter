namespace Spritter.Graphics;

public record struct ShaderUniform(UniformType Type, uint BindPoint, uint BufferSize)
{
    public UniformType Type = Type;
    
    public uint BindPoint = BindPoint;
    
    public uint BufferSize = BufferSize;
}