namespace Spritter.Graphics;

public struct Uniform
{
    public UniformType Type;
    
    public string Name;

    public uint BufferSize;

    public Uniform(UniformType type, string name, uint bufferSize = 0)
    {
        Type = type;
        Name = name;
        BufferSize = bufferSize;
    }
}