#pragma once

#ifndef SP_TEXTUREBATCHER_MAXDRAWS
#define SP_TEXTUREBATCHER_MAXDRAWS 4096
#endif

#include <array>
#include <vector>
#include <optional>

#include "GraphicsDevice.h"
#include "Spritter/Math/Math.h"

namespace Spritter::Graphics
{
    class SpriteRenderer
    {
        static constexpr uint32_t NumVertices = 4;
        static constexpr uint32_t NumIndices = 6;

        static constexpr uint32_t MaxVertices = NumVertices * SP_TEXTUREBATCHER_MAXDRAWS;
        static constexpr uint32_t MaxIndices = NumIndices * SP_TEXTUREBATCHER_MAXDRAWS;

        struct Vertex
        {
            Math::Vector2f Position;
            Math::Vector2f TexCoord;
            Math::Color Tint;
        };

        struct BatchItem
        {
            Graphics::Texture& Texture;
            Math::Vector2f TopLeft;
            Math::Vector2f TopRight;
            Math::Vector2f BottomLeft;
            Math::Vector2f BottomRight;
            std::optional<Math::Rectangle> Source;
            Math::Color Tint;
        };

        GraphicsDevice& _device;

        std::array<Vertex, MaxVertices> _vertices{};
        std::array<uint32_t, MaxIndices> _indices{};

        std::unique_ptr<Shader> _defaultShader;
        std::unique_ptr<Renderable> _renderable;

        std::unique_ptr<Texture> _whiteTexture;

        std::vector<BatchItem> _items;

    public:
        explicit SpriteRenderer(GraphicsDevice& device);

        void Draw(Texture& texture, const Math::Vector2f& topLeft, const Math::Vector2f& topRight,
                  const Math::Vector2f& bottomLeft, const Math::Vector2f& bottomRight,
                  const std::optional<Math::Rectangle>& source, const Math::Color& tint);

        void Draw(Texture& texture, const Math::Vector2f& position, const std::optional<Math::Rectangle>& source = {},
                  const Math::Color& tint = Math::Color::White());

        void Draw(Texture& texture, const Math::Matrixf& matrix, const std::optional<Math::Rectangle>& source = {},
                  const Math::Color& tint = Math::Color::White());

        void Draw(Texture& texture, const Math::Vector2f& position, const std::optional<Math::Rectangle>& source,
                  const Math::Color& tint, float rotation, const Math::Vector2f& scale = Math::Vector2f::One(),
                  const Math::Vector2f& origin = Math::Vector2f::Zero())
        {
            Draw(texture,
                 Math::Matrixf::Translate(-origin.X, -origin.Y, 0) * Math::Matrixf::Scale(scale.X, scale.Y, 0) *
                 Math::Matrixf::RotateZ(rotation) * Math::Matrixf::Translate(position.X, position.Y, 0), source, tint);
        }

        void Draw(Texture& texture, const Math::Vector2f& position, const float rotation,
                  const Math::Vector2f& scale = Math::Vector2f::One(),
                  const Math::Vector2f& origin = Math::Vector2f::Zero())
        {
            Draw(texture, position, {}, Math::Color::White(), rotation, scale, origin);
        }

        void DrawFilledRectangle(const Math::Vector2f& position, const Math::Size& size, const Math::Color& color);
        void DrawBorderRectangle(const Math::Vector2f& position, const Math::Size& size, int32_t borderSize, const Math::Color& color);

        void DrawRectangle(const Math::Vector2f& position, const Math::Size& size, const Math::Color& fillColor, int32_t borderSize, const Math::Color& borderColor)
        {
            DrawFilledRectangle(position, size, fillColor);
            DrawBorderRectangle(position, size, borderSize, borderColor);
        }

        void Render(const Math::Matrixf& transform = Math::Matrixf::Identity());

    private:
        void Flush(Texture* texture, uint32_t numDraws);
    };
}