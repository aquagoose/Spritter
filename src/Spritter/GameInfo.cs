using System.Drawing;

namespace Spritter;

public struct GameInfo
{
    public string Name;

    public Size Size;

    public GameInfo(string name)
    {
        Name = name;
        Size = new Size(1280, 720);
    }
}