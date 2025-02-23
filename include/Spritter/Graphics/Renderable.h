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

        ShaderAttribute* ShaderLayout;
        int NumAttributes;

        uint32_t ShaderStride;

        bool Dynamic;
    };

    class Renderable
    {
    public:
        virtual ~Renderable() = default;

        virtual void Draw() = 0;
    };
}
