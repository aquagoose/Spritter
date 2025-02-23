#pragma once

#include <cstdint>

#include "Shader.h"

namespace Spritter::Graphics
{
    struct RenderableDefinition
    {
        void* Vertices;
        uint32_t NumVertices;

        uint32_t* Indices;
        uint32_t NumIndices;

        Graphics::Shader* Shader;
        uint32_t ShaderStride;

        ShaderAttribute* ShaderLayout;
        int NumAttributes;

        ShaderUniform* Uniforms;
        int NumUniforms;

        bool Dynamic;
    };

    struct RenderableUpdateInfo
    {
        void* Vertices;
        uint32_t NumVertices;

        void* Indices;
        uint32_t NumIndices;
    };

    class Renderable
    {
    public:
        virtual ~Renderable() = default;

        virtual void Update(const RenderableUpdateInfo& info) = 0;

        virtual void Draw(uint32_t numDraws) = 0;
    };
}
