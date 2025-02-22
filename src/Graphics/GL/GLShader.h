#pragma once

#include <glad/glad.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::GL
{
    class GLShader : public Shader
    {
    public:
        GLuint Program;

        GLShader(ShaderAttachment* attachments, int numAttachments);
        ~GLShader();
    };
}
