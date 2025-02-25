#pragma once

#include <cstdint>
#include <glad/glad.h>
#include <unordered_map>

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

        GLShader* _shader;
        uint32_t _stride;

        std::unordered_map<uint32_t, GLuint> _uniformBuffers;

    public:
        explicit GLRenderable(const RenderableDefinition& definition);
        ~GLRenderable() override;

        void Update(const RenderableUpdateInfo& info) override;

        void PushUniformData(uint32_t bindPoint, uint32_t dataSize, void* data) override;

        void PushTexture(uint32_t bindPoint, Texture* texture) override;

        void Draw(uint32_t numDraws) override;
    };
}