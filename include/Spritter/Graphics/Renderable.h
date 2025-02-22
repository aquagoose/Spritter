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

        bool Dynamic;
    };

    class Renderable
    {

    };
}
