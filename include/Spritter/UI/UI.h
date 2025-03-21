#pragma once

#include "Control.h"

namespace Spritter::UI
{
    class UIManager
    {
        Graphics::SpriteRenderer& _spriteRenderer;
        std::unique_ptr<Control> _baseControl;

    public:
        explicit UIManager(Graphics::SpriteRenderer& spriteRenderer) : _spriteRenderer(spriteRenderer)
        {
            _baseControl = nullptr;
        }

        [[nodiscard]] Control& BaseControl() const
        {
            return *_baseControl;
        }

        void SetBaseControl(std::unique_ptr<Control> control)
        {
            _baseControl = std::move(control);
        }

        void Update(const float dt) const
        {
            _baseControl->Update(dt);
        }

        void Draw() const
        {
            _baseControl->Draw(_spriteRenderer);
        }
    };
}