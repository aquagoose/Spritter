#pragma once

#include "Spritter/Graphics/SpriteRenderer.h"

namespace Spritter::UI
{
    class Control
    {
    public:
        virtual ~Control();

        virtual void Update(float dt);
        virtual void Draw(Graphics::SpriteRenderer& renderer) = 0;
    };
}
