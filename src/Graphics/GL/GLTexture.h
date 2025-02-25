#pragma once

#include <cstdint>

#include <glad/glad.h>

#include "Spritter/Graphics/Texture.h"

namespace Spritter::Graphics::GL
{
    class GLTexture final : public Texture
    {
    public:
        GLuint Texture;

        GLTexture(uint32_t width, uint32_t height, PixelFormat format, void* data);
        ~GLTexture() override;
    };
}
