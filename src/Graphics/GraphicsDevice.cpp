#include "Spritter/Graphics/GraphicsDevice.h"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Spritter::Graphics
{
    std::unique_ptr<Texture> GraphicsDevice::CreateTexture(const std::string& path)
    {
        int w, h;
        void* data = stbi_load(path.c_str(), &w, &h, nullptr, 4);

        if (!data)
            throw std::runtime_error("Failed to load image: " + std::string(stbi_failure_reason()));

        auto texture = CreateTexture(static_cast<uint32_t>(w), static_cast<uint32_t>(h), PixelFormat::R8G8B8A8_UNorm, data);

        stbi_image_free(data);

        return std::move(texture);
    }
}
