#pragma once

#include <cstdint>

#include <glad/glad.h>

#include "Spritter/Graphics/Texture.h"

namespace Spritter::Graphics::GL
{
    class GLTexture final : public Texture
    {
        Math::Size _size;
        GLenum _pixelFormat;
        GLenum _pixelType;

    public:
        GLuint Texture{};

        GLTexture(uint32_t width, uint32_t height, PixelFormat format, void* data);
        ~GLTexture() override;

        [[nodiscard]] Math::Size Size() const override;

        void Update(const Math::Rectangle& region, void* data) override;
    };
}
