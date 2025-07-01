namespace Spritter.Graphics;

public struct VertexElement
{
    public string Name;

    public VertexElementType Type;

    public uint ByteOffset;

    public VertexElement(string name, VertexElementType type, uint byteOffset)
    {
        Name = name;
        Type = type;
        ByteOffset = byteOffset;
    }
}