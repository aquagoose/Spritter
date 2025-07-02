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

        _texture = GraphicsDevice.CreateTexture("/home/aqua/Pictures/DEBUG.png");
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);

        //_renderer.Draw(_texture, new Vector2(0, 0), new Vector2(512, 0), new Vector2(0, 256), new Vector2(512, 512));
        //_renderer.Draw(_texture, Vector2.Zero, new Size(1280, 720));
        _renderer.Draw(_texture, Vector2.Zero, new Rectangle(0, 32, 64, 256));
        _renderer.Draw(_texture, Matrix3x2.CreateRotation(1) * Matrix3x2.CreateTranslation(100, 100), new Rectangle(64, 64, 128, 64));
        //_renderer.Draw(_texture, Vector2.Zero, 0.5f, null, new Vector2(2, 1), new Vector2(64), Color.Aqua);
        _renderer.Render();
    }

    public override void Dispose()
    {
        _texture.Dispose();
        _renderer.Dispose();
        
        base.Dispose();
    }
}