#include <iostream>

#include <Spritter/Spritter.h>
#include <Spritter/UI/UI.h>

using namespace Spritter;
using namespace Spritter::Graphics;
using namespace Spritter::Math;
using namespace Spritter::UI;

class TestGame final : public Game
{
    std::unique_ptr<Font> _font;
    std::unique_ptr<UIManager> _ui;

    void Initialize() override
    {
        _font = std::make_unique<Font>(*GraphicsDevice, "/home/aqua/Documents/Roboto-Regular.ttf");

        _ui = std::make_unique<UIManager>(*GraphicsDevice, Theme::DefaultLight(*_font));

        auto label = std::make_unique<Label>(*_ui, L"Hello World!", 48);
        _ui->SetBaseControl(std::move(label));
    }

    void Update(const float dt) override
    {
        _ui->Update(dt);
    }

    void Draw() override
    {
        GraphicsDevice->Clear(Color::RebeccaPurple());

        _ui->Draw();
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