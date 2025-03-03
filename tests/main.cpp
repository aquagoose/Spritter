#include <iostream>

#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class TestGame final : public Game
{
    std::unique_ptr<Renderable> _renderable;

    void Initialize() override
    {
        float vertices[] =
        {
            -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
            -0.5f, +0.5f,    0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f,    0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f,    0.0f, 0.0f, 0.0f
        };

        uint32_t indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };


    }

    void Draw() override
    {
        GraphicsDevice->Clear(Color::RebeccaPurple());
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