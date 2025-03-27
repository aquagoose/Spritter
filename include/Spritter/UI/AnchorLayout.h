#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Spritter/Math/Math.h"

#include "Control.h"
#include "UIManager.h"

namespace Spritter::UI
{
    enum class AnchorPoint
    {
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    struct AnchorControl
    {
        AnchorPoint Anchor;
        Math::Vector2i Offset;
        std::shared_ptr<Control> Control;

        Math::Vector2i AbsPosition;
    };

    class AnchorLayout final : public Control
    {
        std::vector<AnchorControl> _controls;
        bool _invalidateLayout{};
        Math::Size _layoutSize{};

    public:
        explicit AnchorLayout(const UIManager& manager);

        void InvalidateLayout()
        {
            _invalidateLayout = true;
        }

        void AddControl(const std::string& name, AnchorPoint anchor, const Math::Vector2i& offset, const std::shared_ptr<Control>& control);

        Math::Size Size() override
        {
            return _layoutSize;
        }

        void Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured) override;
        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
