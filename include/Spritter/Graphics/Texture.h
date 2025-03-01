#pragma once

#include "Spritter/Math/Math.h"

namespace Spritter::Graphics
{
    enum class PixelFormat
    {
        R8G8B8A8_UNorm
    };

    class Texture
    {
    public:
        virtual ~Texture() = default;

        [[nodiscard]] virtual Math::Size Size() const = 0;

        virtual void Update(const Math::Rectangle& region, void* data) = 0;
    };
}
