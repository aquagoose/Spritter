#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class MyGame final : public Game
{
    std::unique_ptr<SpriteRenderer> _renderer;
    std::unique_ptr<Font> _font;

    void Initialize() override
    {
        _renderer = std::make_unique<SpriteRenderer>(*GraphicsDevice);
        _font = std::make_unique<Font>(*GraphicsDevice, "Content/NotoSansJP-Regular.ttf");
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