using System.Drawing;
using System.Reflection;

namespace Spritter;

public struct GameOptions()
{
    public string Name = Assembly.GetEntryAssembly()?.GetName().Name ?? "Spritter";

    public Size Size = new(1280, 720);
}