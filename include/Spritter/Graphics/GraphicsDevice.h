#pragma once

#include "../Math/Color.h"

namespace Spritter::Graphics
{
    class GraphicsDevice
    {
    public:
        virtual void Clear(const Math::Color& color) = 0;

        virtual void Present() = 0;
    };
}