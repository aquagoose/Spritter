#include <iostream>

#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class TestGame final : public Game
{
    std::unique_ptr<TextureBatcher> _batcher;
    std::unique_ptr<Texture> _texture;
    std::unique_ptr<Font> _font;

    Vector2f _position{};
    float _rot{};

    void Initialize() override
    {
        //Time::SetTargetFPS(120);
        //GraphicsDevice->SetVSyncMode(false);

        _batcher = std::make_unique<TextureBatcher>(GraphicsDevice.get());
        _texture = GraphicsDevice->CreateTexture("/home/aqua/Pictures/BAGELMIP.png");
        _font = std::make_unique<Font>(*GraphicsDevice, "/home/aqua/Documents/Roboto-Regular.ttf");
    }

    void Update(const float dt) override
    {
        std::cout << Time::TotalFrames() << std::endl;

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

        _rot += dt;
    }

    void Draw() override
    {
        GraphicsDevice->Clear(Color::RebeccaPurple());

        _batcher->Draw(_texture.get(), _position);

        _font->Draw(*_batcher, { 0, 0 }, "hello", 256);

        _batcher->Render();
    }
};

int main(int argc, char* argv[])
{
    GameOptions options
    {
        /* Name: */ "Spritter Test",
        /* Size: */ { 1280, 720 },

        /* Resizable: */ true,
        /* FullscreenMode: */ FullscreenMode::Windowed,

        /* VSync: */ true,
        /* TargetFPS: */ 0 // Unlimited FPS, ignored if VSync enabled
    };

    TestGame game;
    game.Run(options);

    return 0;
}