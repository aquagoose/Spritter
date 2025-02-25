#pragma once

#ifndef SP_TEXTUREBATCHER_MAXDRAWS
#define SP_TEXTUREBATCHER_MAXDRAWS 4096
#endif

#include <array>
#include <vector>

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

        struct BatchItem
        {
            Graphics::Texture* Texture;
            Vector2f TopLeft;
            Vector2f TopRight;
            Vector2f BottomLeft;
            Vector2f BottomRight;
            Color Tint;
        };

        std::array<Vertex, MaxVertices> _vertices{};
        std::array<uint32_t, MaxIndices> _indices{};

        std::unique_ptr<Shader> _defaultShader;
        std::unique_ptr<Renderable> _renderable;

        std::vector<BatchItem> _items;

    public:
        explicit TextureBatcher(GraphicsDevice* device);

        void Draw(Texture* texture, const Vector2f& topLeft, const Vector2f& topRight, const Vector2f& bottomLeft, const Vector2f& bottomRight, const Color& tint);

        void Render();

    private:
        void Flush(Texture* texture, uint32_t numDraws);
    };
}