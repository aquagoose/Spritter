#include "Spritter/UI/UIManager.h"

#include <iostream>

namespace Spritter::UI
{
    UIManager::UIManager(Graphics::GraphicsDevice& device, const UI::Theme& theme) : Theme(theme)
    {
        _spriteRenderer = std::make_unique<Graphics::SpriteRenderer>(device);
        _baseControl = nullptr;
    }

    void UIManager::SetBaseControl(const std::shared_ptr<Control>& control)
    {
        _baseControl = control;
    }

    void UIManager::Update(const float dt) const
    {
        if (!_baseControl)
            return;

        bool mouseCaptured = false;
        _baseControl->Update(dt, Math::Vector2i::Zero(), &mouseCaptured);

        std::cout << mouseCaptured << std::endl;
    }

    void UIManager::Draw() const
    {
        if (!_baseControl)
            return;

        _baseControl->Draw(*_spriteRenderer, Math::Vector2i::Zero());
        _spriteRenderer->Render();
    }
}
