#include "Spritter/UI/AnchorLayout.h"

namespace Spritter::UI
{
    void AnchorLayout::AddControl(const std::string& name, AnchorPoint anchor, const Math::Vector2i& offset, const std::shared_ptr<Control>& control)
    {
        auto anchorControl = AnchorControl
        {
            anchor,
            offset,
            control,
            Math::Vector2i::Zero()
        };

        _controls.push_back(anchorControl);
    }

    void AnchorLayout::Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured)
    {
        if (parentSize != _layoutSize)
            InvalidateLayout();

        if (_invalidateLayout)
        {
            _invalidateLayout = false;

            for (auto& control : _controls)
            {
                Math::Vector2i position;
                const Math::Size controlSize = control.Control->Size();

                switch (control.Anchor)
                {
                    case AnchorPoint::TopLeft:
                        position = { 0, 0 };
                        break;
                    case AnchorPoint::TopCenter:
                        position = { parentSize.Width / 2 - controlSize.Width / 2, 0 };
                        break;
                    case AnchorPoint::TopRight:
                        position = { parentSize.Width - controlSize.Width, 0 };
                        break;
                    case AnchorPoint::MiddleLeft:
                        position = { 0, parentSize.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::MiddleCenter:
                        position = { parentSize.Width / 2 - controlSize.Width / 2, parentSize.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::MiddleRight:
                        position = { parentSize.Width - controlSize.Width, parentSize.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::BottomLeft:
                        position = { 0, parentSize.Height - controlSize.Height };
                        break;
                    case AnchorPoint::BottomCenter:
                        position = { parentSize.Width / 2 - controlSize.Width / 2, parentSize.Height - controlSize.Height };
                        break;
                    case AnchorPoint::BottomRight:
                        position = { parentSize.Width - controlSize.Width, parentSize.Height - controlSize.Height };
                        break;
                }

                position += control.Offset;

                control.AbsPosition = position;
            }
        }

        for (auto control = _controls.rbegin(); control != _controls.rend(); ++control)
        {
            control->Control->Update(dt, control->AbsPosition + position, parentSize, mouseCaptured);
        }
    }

    void AnchorLayout::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        for (const auto& control : _controls)
            control.Control->Draw(renderer, control.AbsPosition + position);
    }
}
