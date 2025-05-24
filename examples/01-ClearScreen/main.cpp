#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

// The main game class. Must derive from Spritter::Game.
class MyGame final : public Game
{
    // Called once, when the game is ready. Create and load resources in here.
    void Initialize() override
    {

    }

    // Called once per frame. Perform game logic and other tasks in here.
    void Update(const float dt) override
    {

    }

    // Called once per frame. Perform drawing in here.
    void Draw() override
    {
        // Clear the window to a cornflower blue color.
        GraphicsDevice->BeginRendering(Color::CornflowerBlue());
        GraphicsDevice->EndRendering();
    }
};

int main(int argc, char* argv[])
{
    // Describes how the game will be created.
    const GameOptions options
    {
        /* Name: */ "01 - Clear Screen",
        /* Size: */ { 1280, 720 },

        /* Resizable: */ true,
        /* FullscreenMode: */ FullscreenMode::Windowed,

        /* VSync: */ true,
        /* TargetFPS: */ 0 // Unlimited FPS, ignored if VSync enabled
    };
    MyGame game;
    game.Run(options);

    return 0;
}