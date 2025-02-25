#pragma once

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
    };
}
