using System.Drawing;

namespace Spritter;

public record struct GameOptions
{
    public string Name;

    public Size Size;

    public GameOptions(string name, Size size)
    {
        Name = name;
        Size = size;
    }
}