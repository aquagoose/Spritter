#include <Spritter/Game.h>

class TestGame : public Spritter::Game
{
    void Draw() override
    {
        GraphicsDevice()->Clear();
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