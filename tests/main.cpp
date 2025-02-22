#include <Spritter/Game.h>

int main(int argc, char* argv[])
{
    Spritter::GameOptions options
    {
        "Spritter Test",
        { 1280, 720 }
    };

    Spritter::Game game(options);

    game.Run();

    return 0;
}