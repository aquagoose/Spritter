#pragma once

#include <glad/glad.h>

#include "Spritter/Graphics/Renderable.h"
#include "GLShader.h"

namespace Spritter::Graphics::GL
{
    class GLRenderable : public Renderable
    {
    private:
        GLuint _vao;
        GLuint _vbo;
        GLuint _ebo;

        GLShader* Shader;

    public:
        explicit GLRenderable(const RenderableDefinition& definition);
        ~GLRenderable();
    };
}