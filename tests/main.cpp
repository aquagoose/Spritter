#include <Spritter/Game.h>

using namespace Spritter;
using namespace Spritter::Graphics;

const char* VertexShader = R"(
#version 330 core

in vec2 aPosition;
in vec3 aColor;

out vec3 frag_Color;

void main()
{
    gl_Position = vec4(aPosition, 0.0, 1.0);
    frag_Color = aColor;
}
)";

const char* PixelShader = R"(
#version 330 core

in vec3 frag_Color;

out vec4 out_Color;

void main()
{
    out_Color = vec4(frag_Color, 1.0);
}
)";

class TestGame : public Game
{
    std::unique_ptr<Shader> _shader;
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

        ShaderAttachment attachments[]
        {
            { ShaderStage::Vertex, VertexShader },
            { ShaderStage::Pixel, PixelShader }
        };
        _shader = GraphicsDevice()->CreateShader(attachments, 2);

        ShaderAttribute attributes[]
        {
            { "aPosition", AttributeType::Float2, 0 },
            { "aColor", AttributeType::Float3, 8 }
        };

        RenderableDefinition definition
        {
            vertices,
            sizeof(vertices),
            indices,
            sizeof(indices),
            _shader.get(),
            attributes,
            2,
            5 * sizeof(float),
            false
        };

        _renderable = GraphicsDevice()->CreateRenderable(definition);
    }

    void Draw() override
    {
        GraphicsDevice()->Clear({ 0.25f, 0.5f, 1.0f });

        _renderable->Draw();
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