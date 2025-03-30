using System.Drawing;

namespace Spritter.Tests;

public class TestGame : Game
{
    public TestGame(in GameOptions options) : base(in options) { }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
    }
}