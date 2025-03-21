#include "Spritter/UI/AnchorLayout.h"

namespace Spritter::UI
{
    AnchorLayout::AnchorLayout(const UIManager& manager) : Control(manager.Theme)
    {
        InvalidateLayout();
    }

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


    void AnchorLayout::Update(float dt, const Math::Vector2i& position, bool* mouseCaptured)
    {
        Math::Size size = { 1280, 720 };

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
                        position = { size.Width / 2 - controlSize.Width / 2, 0 };
                        break;
                    case AnchorPoint::TopRight:
                        position = { size.Width - controlSize.Width, 0 };
                        break;
                    case AnchorPoint::MiddleLeft:
                        position = { 0, size.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::MiddleCenter:
                        position = { size.Width / 2 - controlSize.Width / 2, size.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::MiddleRight:
                        position = { size.Width - controlSize.Width, size.Height / 2 - controlSize.Height / 2 };
                        break;
                    case AnchorPoint::BottomLeft:
                        position = { 0, size.Height - controlSize.Height };
                        break;
                    case AnchorPoint::BottomCenter:
                        position = { size.Width / 2 - controlSize.Width / 2, size.Height - controlSize.Height };
                        break;
                    case AnchorPoint::BottomRight:
                        position = { size.Width - controlSize.Width, size.Height - controlSize.Height };
                        break;
                }

                position += control.Offset;

                control.AbsPosition = position;
            }
        }

        for (size_t i = _controls.size() - 1; i > 0; i--)
        {
            const auto& control = _controls[i];
            control.Control->Update(dt, control.AbsPosition + position, mouseCaptured);
        }
    }

    void AnchorLayout::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        for (const auto& control : _controls)
            control.Control->Draw(renderer, control.AbsPosition + position);
    }
}
