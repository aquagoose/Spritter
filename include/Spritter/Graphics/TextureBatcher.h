#pragma once

#ifndef SP_TEXTUREBATCHER_MAXDRAWS
#define SP_TEXTUREBATCHER_MAXDRAWS 4096
#endif

#include <array>

#include "GraphicsDevice.h"
#include "Spritter/Math/Math.h"

using namespace Spritter::Math;

namespace Spritter::Graphics
{
    class TextureBatcher
    {
        static constexpr uint32_t NumVertices = 4;
        static constexpr uint32_t NumIndices = 6;

        static constexpr uint32_t MaxVertices = NumVertices * SP_TEXTUREBATCHER_MAXDRAWS;
        static constexpr uint32_t MaxIndices = NumIndices * SP_TEXTUREBATCHER_MAXDRAWS;

        struct Vertex
        {
            Vector2f Position;
            Vector2f TexCoord;
            Color Tint;
        };

        std::array<Vertex, MaxVertices> _vertices{};
        std::array<uint32_t, MaxIndices> _indices{};

        std::unique_ptr<Shader> _defaultShader;
        std::unique_ptr<Renderable> _renderable;

    public:
        explicit TextureBatcher(GraphicsDevice* device);
    };
}