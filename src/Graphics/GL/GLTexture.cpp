#include "GLTexture.h"

#include <stdexcept>

namespace Spritter::Graphics::GL
{
    GLTexture::GLTexture(uint32_t width, uint32_t height, PixelFormat format, void* data)
    {
        _size = { static_cast<int32_t>(width), static_cast<int32_t>(height) };

        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        GLint internalFormat;

        switch (format)
        {
            case PixelFormat::R8G8B8A8_UNorm:
                internalFormat = GL_RGBA8;
                _pixelFormat = GL_RGBA;
                _pixelType = GL_UNSIGNED_BYTE;
                break;
            default:
                throw std::runtime_error("Invalid pixel format.");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0,
                     _pixelFormat, _pixelType, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    GLTexture::~GLTexture()
    {
        glDeleteTextures(1, &Texture);
    }

    Math::Size GLTexture::Size() const
    {
        return _size;
    }

    void GLTexture::Update(const Math::Rectangle& region, void* data)
    {
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexSubImage2D(GL_TEXTURE_2D, 0, region.X(), region.Y(), region.Width(), region.Height(), _pixelFormat,
                        _pixelType, data);
    }
}
