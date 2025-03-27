#include "Spritter/UI/UIManager.h"

namespace Spritter::UI
{
    UIManager::UIManager(Graphics::GraphicsDevice& device, const UI::Theme& theme) : _device(device), Theme(theme)
    {
        _spriteRenderer = std::make_unique<Graphics::SpriteRenderer>(_device);
        _baseControl = nullptr;
    }

    void UIManager::SetBaseControl(const std::shared_ptr<Control>& control)
    {
        _baseControl = control;
    }

    void UIManager::Update(const float dt)
    {
        if (!_baseControl)
            return;

        _baseSize = _device.Viewport().Size;

        bool mouseCaptured = false;
        _baseControl->Update(dt, Math::Vector2i::Zero(), _baseSize, &mouseCaptured);
    }

    void UIManager::Draw() const
    {
        if (!_baseControl)
            return;

        _baseControl->Draw(*_spriteRenderer, Math::Vector2i::Zero());
        _spriteRenderer->Render();
    }
}
