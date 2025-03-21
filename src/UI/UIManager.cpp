#include "Spritter/UI/UIManager.h"

namespace Spritter::UI
{
    UIManager::UIManager(Graphics::GraphicsDevice& device, const UI::Theme& theme) : Theme(theme)
    {
        _spriteRenderer = std::make_unique<Graphics::SpriteRenderer>(device);
        _baseControl = nullptr;
    }

    void UIManager::SetBaseControl(std::unique_ptr<Control> control)
    {
        _baseControl = std::move(control);
    }

    void UIManager::Update(const float dt) const
    {
        if (!_baseControl)
            return;

        _baseControl->Update(dt);
    }

    void UIManager::Draw() const
    {
        if (!_baseControl)
            return;

        _baseControl->Draw(*_spriteRenderer, Math::Vector2i::Zero());
        _spriteRenderer->Render();
    }
}
