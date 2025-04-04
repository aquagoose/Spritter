using System.Drawing;
using System.Numerics;
using Spritter.Graphics;

namespace Spritter.Tests;

public class TestGame : Game
{
    private readonly SpriteRenderer _renderer;
    private readonly Texture _texture;
    private readonly Texture _texture2;

    public TestGame(in GameOptions options) : base(in options)
    {
        _renderer = new SpriteRenderer(GraphicsDevice);
        _texture = GraphicsDevice.CreateTexture("/home/aqua/Pictures/awesomeface.png");
        _texture2 = GraphicsDevice.CreateTexture("/home/aqua/Pictures/BAGELMIP.png");
    }

    protected override void Update(float dt)
    {
        base.Update(dt);
    }

    private float _value;
    
    protected override void Draw()
    {
        base.Draw();

        _value += 0.1f;
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
        _renderer.Draw(_texture, new Vector2(0, 0));
        _renderer.Draw(_texture2, new Vector2(200, 200), _value);

        _renderer.Render();
    }

    public override void Dispose()
    {
        _texture2.Dispose();
        _texture.Dispose();
        _renderer.Dispose();
        
        base.Dispose();
    }
}