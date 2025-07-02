using System.Drawing;
using Spritter;

namespace Tests.Spritter;

public class TestGame : Game
{
    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
    }
}