#include <iostream>

#include <Spritter/Game.h>
#include <Spritter/Graphics/TextureBatcher.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class TestGame final : public Game
{
    std::unique_ptr<TextureBatcher> _batcher;
    std::unique_ptr<Texture> _texture;

    void Initialize() override
    {
        _batcher = std::make_unique<TextureBatcher>(GraphicsDevice.get());

        _texture = GraphicsDevice->CreateTexture("/home/aqua/Pictures/awesomeface.png");
    }

    void Draw() override
    {
        GraphicsDevice->Clear({ 0.25f, 0.5f, 1.0f });

        _batcher->Draw(_texture.get(), { 0, 0 }, { 100, 0 },  { 0, 100 }, { 200, 100 }, { 1.0f, 1.0f, 1.0f });
        _batcher->Render();
    }
};

int main(int argc, char* argv[])
{
    GameOptions options
    {
        "Spritter Test",
        { 1280, 720 }
    };

    TestGame game;
    game.Run(options);

    return 0;
}