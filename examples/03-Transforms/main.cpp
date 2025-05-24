#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class MyGame final : public Game
{
    std::unique_ptr<SpriteRenderer> _renderer;
    std::unique_ptr<Texture> _sprite;

    Vector2f _position{};
    float _value{};

    void Initialize() override
    {
        _renderer = std::make_unique<SpriteRenderer>(*GraphicsDevice);
        _sprite = GraphicsDevice->CreateTexture("Content/bagel.png");
    }

    void Update(const float dt) override
    {
        _value += dt;

        _position.X = 100 + (std::sin(_value) + 1) * 0.5f * 500;
        _position.Y = 100 + (std::cos(_value * 3) + 1) * 0.5f * 200;

        if (_value >= M_PI * 2)
            _value -= M_PI * 2;
    }

    void Draw() override
    {
        GraphicsDevice->BeginRendering(Color::CornflowerBlue());

        _renderer->Draw(*_sprite, _position, _value, { 2, 1 });
        _renderer->Render();

        GraphicsDevice->EndRendering();
    }
};

int main(int argc, char* argv[])
{
    const GameOptions options
    {
        /* Name: */ "03 - Transforms",
        /* Size: */ { 1280, 720 },
        /* Resizable: */ true,
    };
    MyGame game;
    game.Run(options);

    return 0;
}