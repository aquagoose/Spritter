#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class MyGame final : public Game
{
    std::unique_ptr<SpriteRenderer> _renderer;
    std::unique_ptr<Font> _font;

    Vector2f _position{};
    float _value{};

    void Initialize() override
    {
        _renderer = std::make_unique<SpriteRenderer>(*GraphicsDevice);
        _font = std::make_unique<Font>(*GraphicsDevice, "Content/NotoSansJP-Regular.ttf");
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
        GraphicsDevice->Clear(Color::CornflowerBlue());

        _font->Draw(*_renderer, { 50, 50 }, "Hello! This is some text.", 48);
        _font->Draw(*_renderer, { 50, 120 }, "Here's some text in a different size.", 70);
        _font->Draw(*_renderer, { 50, 190 }, U"これは日本語のテキストです！", 48);
        _renderer->Render();
    }
};

int main(int argc, char* argv[])
{
    const GameOptions options
    {
        /* Name: */ "05 - Text",
        /* Size: */ { 1280, 720 },
        /* Resizable: */ true,
    };
    MyGame game;
    game.Run(options);

    return 0;
}