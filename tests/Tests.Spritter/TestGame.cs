using System.Drawing;
using System.Numerics;
using Spritter;
using Spritter.Graphics;

namespace Tests.Spritter;

public class TestGame : Game
{
    private SpriteRenderer _renderer = null!;
    private Texture _texture = null!;

    protected override void Initialize()
    {
        base.Initialize();

        _renderer = new SpriteRenderer(GraphicsDevice);

        _texture = GraphicsDevice.CreateTexture("/home/aqua/Pictures/awesomeface.png");
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);

        _renderer.Draw(_texture, new Vector2(0, 0), new Vector2(512, 0), new Vector2(0, 512), new Vector2(512, 512), Color.White);
        _renderer.Render();
    }

    public override void Dispose()
    {
        _texture.Dispose();
        
        base.Dispose();
    }
}