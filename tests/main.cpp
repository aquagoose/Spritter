#include <Spritter/Game.h>
#include <Spritter/Graphics/TextureBatcher.h>

using namespace Spritter;
using namespace Spritter::Graphics;

class TestGame : public Game
{
    std::unique_ptr<TextureBatcher> _batcher;

    void Initialize() override
    {
        _batcher = std::make_unique<TextureBatcher>(GraphicsDevice.get());
    }

    void Draw() override
    {
        GraphicsDevice->Clear({ 0.25f, 0.5f, 1.0f });
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