#pragma once

#include <cstdint>

namespace Spritter::Graphics
{
    struct RenderableDefinition
    {
        void* Vertices;
        uint32_t NumVertices;

        void* Indices;
        uint32_t NumIndices;

        bool Dynamic;
    };

    class Renderable
    {

    };
}
