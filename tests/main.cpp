#include <Spritter/Game.h>

class TestGame : public Spritter::Game
{
    void Draw() override
    {
        GraphicsDevice()->Clear({ 0.25f, 0.5f, 1.0f });
    }
};

int main(int argc, char* argv[])
{
    Spritter::GameOptions options
    {
        "Spritter Test",
        { 1280, 720 }
    };

    TestGame game;
    game.Run(options);

    return 0;
}