#pragma once

#include <cstdint>
#include <glad/glad.h>

#include "Spritter/Graphics/Renderable.h"
#include "GLShader.h"

namespace Spritter::Graphics::GL
{
    class GLRenderable : public Renderable
    {
    private:
        uint32_t _numDraws;

        GLuint _vao;
        GLuint _vbo;
        GLuint _ebo;

        GLShader* _shader;
        uint32_t _stride;

    public:
        explicit GLRenderable(const RenderableDefinition& definition);
        ~GLRenderable() override;

        void Draw() override;
    };
}