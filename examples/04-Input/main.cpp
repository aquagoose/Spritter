#include <Spritter/Spritter.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;

class MyGame final : public Game
{
    std::unique_ptr<SpriteRenderer> _renderer;
    std::unique_ptr<Texture> _sprite;

    Vector2f _position{};

    void Initialize() override
    {
        _renderer = std::make_unique<SpriteRenderer>(*GraphicsDevice);
        _sprite = GraphicsDevice->CreateTexture("Content/bagel.png");
    }

    void Update(const float dt) override
    {
        constexpr float standardMoveSpeed = 200;
        constexpr float fastMoveSpeed = 400;

        // Multiply our movement speed by the delta time, which is the amount of time, in seconds, the last frame took
        // to process. You should generally always multiply by the delta time when possible, as not doing so will tie
        // movement to the frame-rate, which is generally undesired behaviour.
        const float moveSpeed = (Input::IsKeyDown(Key::LeftShift) ? fastMoveSpeed : standardMoveSpeed) * dt;

        // IsKeyDown always returns true if the key is held down.
        if (Input::IsKeyDown(Key::Right))
            _position.X += moveSpeed;
        if (Input::IsKeyDown(Key::Left))
            _position.X -= moveSpeed;
        if (Input::IsKeyDown(Key::Up))
            _position.Y -= moveSpeed;
        if (Input::IsKeyDown(Key::Down))
            _position.Y += moveSpeed;

        // IsKeyPressed will only return true on the first frame the key is pressed. It will otherwise always return
        // false, even if the key remains held down.
        if (Input::IsKeyPressed(Key::Escape))
            Close();

        // The same can be said about mouse buttons.
        if (Input::IsMouseButtonDown(MouseButton::Left))
            // The mouse delta is the change in mouse position, in pixels, since the last frame.
            _position += Input::MouseDelta();
        if (Input::IsMouseButtonPressed(MouseButton::Right))
            // The mouse position, in pixels, relative to the top-left corner of the window.
            _position = Input::MousePosition();
    }

    void Draw() override
    {
        GraphicsDevice->BeginRendering(Color::CornflowerBlue());

        _renderer->Draw(*_sprite, _position);
        _renderer->Render();

        GraphicsDevice->EndRendering();
    }
};

int main(int argc, char* argv[])
{
    const GameOptions options
    {
        /* Name: */ "04 - Input",
        /* Size: */ { 1280, 720 },
        /* Resizable: */ true,
    };
    MyGame game;
    game.Run(options);

    return 0;
}