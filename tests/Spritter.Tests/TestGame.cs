using System.Drawing;
using System.Numerics;
using Spritter.Graphics;

namespace Spritter.Tests;

public class TestGame : Game
{
    private readonly SpriteRenderer _renderer;
    private readonly Texture _texture;

    public TestGame(in GameOptions options) : base(in options)
    {
        _renderer = new SpriteRenderer(GraphicsDevice);
        _texture = GraphicsDevice.CreateTexture("/home/aqua/Pictures/BAGELMIP.png");
    }

    protected override void Update(float dt)
    {
        base.Update(dt);
    }

    protected override void Draw()
    {
        base.Draw();
        
        GraphicsDevice.Clear(Color.CornflowerBlue);
        
    }

    public override void Dispose()
    {
        _texture.Dispose();
        _renderer.Dispose();
        
        base.Dispose();
    }
}