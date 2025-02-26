#include <iostream>

#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class TestGame final : public Game
{
    std::unique_ptr<TextureBatcher> _batcher;
    std::unique_ptr<Texture> _texture;

    Vector2f _position{};

    void Initialize() override
    {
        _batcher = std::make_unique<TextureBatcher>(GraphicsDevice.get());

        _texture = GraphicsDevice->CreateTexture("/home/aqua/Pictures/DEBUG.png");
    }

    void Update(const float dt) override
    {
        const float moveSpeed = 100 * dt;

        if (Input::IsKeyDown(Key::Up))
            _position.Y -= moveSpeed;
        if (Input::IsKeyDown(Key::Down))
            _position.Y += moveSpeed;
        if (Input::IsKeyDown(Key::Left))
            _position.X -= moveSpeed;
        if (Input::IsKeyDown(Key::Right))
            _position.X += moveSpeed;

        if (Input::IsKeyPressed(Key::Space))
            std::cout << "Space" << std::endl;

        if (Input::IsMouseButtonDown(MouseButton::Left))
            _position += Input::MouseDelta();
        if (Input::IsMouseButtonPressed(MouseButton::Right))
            _position = Input::MousePosition();

        if (Input::IsKeyPressed(Key::Escape))
            Close();
    }

    void Draw() override
    {
        GraphicsDevice->Clear(Color::RebeccaPurple());

        _batcher->Draw(_texture.get(), _position, {}, Color::White());
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