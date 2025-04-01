namespace Spritter.Graphics;

public record struct ShaderAttribute(AttributeType Type, uint ByteOffset)
{
    public AttributeType Type = Type;

    public uint ByteOffset = ByteOffset;
}