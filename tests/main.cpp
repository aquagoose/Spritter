#include <Spritter/Game.h>

using namespace Spritter;
using namespace Spritter::Graphics;

class TestGame : public Game
{
    std::unique_ptr<Renderable> _renderable;

    void Initialize() override
    {
        float vertices[]
        {
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, +0.5f, 0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, 0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, 0.0f, 0.0f, 0.0f
        };

        uint32_t indices[]
        {
            0, 1, 3,
            1, 2, 3
        };

        RenderableDefinition definition
        {
            vertices,
            sizeof(vertices),
            indices,
            sizeof(indices),
            false
        };

        _renderable = GraphicsDevice()->CreateRenderable(definition);
    }

    void Draw() override
    {
        GraphicsDevice()->Clear({ 0.25f, 0.5f, 1.0f });
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