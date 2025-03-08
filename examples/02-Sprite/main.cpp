#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class MyGame final : public Game
{
    // A SpriteRenderer performs efficient rendering of sprites. This is the primary way to draw sprites in Spritter.
    std::unique_ptr<SpriteRenderer> _renderer;

    // A texture contains the image data for our sprite.
    std::unique_ptr<Texture> _sprite;

    void Initialize() override
    {
        // Create an instance of our sprite renderer. This requires a reference to the GraphicsDevice.
        _renderer = std::make_unique<SpriteRenderer>(*GraphicsDevice);

        // Create our sprite from an image file.
        _sprite = GraphicsDevice->CreateTexture("Content/bagel.png");
    }

    void Draw() override
    {
        GraphicsDevice->Clear(Color::CornflowerBlue());

        // Add the sprite to the draw queue, at position { 0, 0 }. This will place it at the top-left corner of the
        // screen.
        _renderer->Draw(*_sprite, Vector2f::Zero());

        // After we've drawn everything, finally tell the renderer to draw everything to the screen.
        _renderer->Render();
    }
};

int main(int argc, char* argv[])
{
    const GameOptions options
    {
        /* Name: */ "02 - Sprite",
        /* Size: */ { 1280, 720 },
        /* Resizable: */ true,
    };
    MyGame game;
    game.Run(options);

    return 0;
}