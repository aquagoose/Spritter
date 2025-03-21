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

        auto layout = std::make_shared<AnchorLayout>(*_ui);
        _ui->SetBaseControl(layout);

        auto label = std::make_shared<Label>(*_ui, L"Hello World!", 48);
        layout->AddControl("label", AnchorPoint::TopLeft, { 0, 0 }, label);

        layout->AddControl("tlbutton", AnchorPoint::TopLeft, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("tcbutton", AnchorPoint::TopCenter, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("trbutton", AnchorPoint::TopRight, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("mlbutton", AnchorPoint::MiddleLeft, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("mcbutton", AnchorPoint::MiddleCenter, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("mrbutton", AnchorPoint::MiddleRight, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("blbutton", AnchorPoint::BottomLeft, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("bcbutton", AnchorPoint::BottomCenter, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));
        layout->AddControl("brbutton", AnchorPoint::BottomRight, {0, 0},
                           std::make_shared<Button>(*_ui, L"Test", Size(100, 100)));

        layout->AddControl("sneakybutton", AnchorPoint::MiddleCenter, { -50, -50 }, std::make_shared<Button>(*_ui, L"Hello", Size(100, 100)));
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