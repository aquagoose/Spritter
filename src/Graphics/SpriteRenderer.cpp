#include "Spritter/Graphics/SpriteRenderer.h"

#include <iostream>

const char* TBVertexShader = R"(
#version 330 core

in vec2 aPosition;
in vec2 aTexCoord;
in vec4 aTint;

out vec2 frag_TexCoord;
out vec4 frag_Tint;

layout (std140) uniform CameraMatrices
{
    mat4 Projection;
    mat4 Transform;
};

void main()
{
    gl_Position = Projection * Transform * vec4(aPosition, 0.0, 1.0);
    frag_TexCoord = aTexCoord;
    frag_Tint = aTint;
}
)";

const char* TBPixelShader = R"(
#version 330 core

in vec2 frag_TexCoord;
in vec4 frag_Tint;

out vec4 out_Color;

uniform sampler2D uTexture;

void main()
{
    out_Color = texture(uTexture, frag_TexCoord) * frag_Tint;
}
)";

struct CameraMatrices
{
    Spritter::Math::Matrixf Projection;
    Spritter::Math::Matrixf Transform;
};

namespace Spritter::Graphics
{
    SpriteRenderer::SpriteRenderer(GraphicsDevice& device) : _device(device)
    {
        ShaderAttachment attachments[]
        {
            { ShaderStage::Vertex, TBVertexShader },
            { ShaderStage::Pixel, TBPixelShader }
        };
        _defaultShader = device.CreateShader(attachments, 2);

        ShaderAttribute attributes[]
        {
            { "aPosition", AttributeType::Float2, offsetof(Vertex, Position) },
            { "aTexCoord", AttributeType::Float2, offsetof(Vertex, TexCoord) },
            { "aTint", AttributeType::Float4, offsetof(Vertex, Tint) }
        };

        ShaderUniform uniforms[]
        {
            {
                UniformType::ConstantBuffer,
                "CameraMatrices",
                0,
                sizeof(CameraMatrices)
            },
            {
                UniformType::Texture,
                "uTexture",
                0
            }
        };

        const RenderableDefinition definition
        {
            nullptr,
            MaxVertices * sizeof(Vertex),
            nullptr,
            MaxIndices,
            _defaultShader.get(),
            sizeof(Vertex),
            attributes,
            3,
            uniforms,
            1,
            true
        };
        _renderable = device.CreateRenderable(definition);
    }

    void SpriteRenderer::Draw(Texture* texture, const Math::Vector2f& topLeft, const Math::Vector2f& topRight,
                              const Math::Vector2f& bottomLeft, const Math::Vector2f& bottomRight,
                              const std::optional<Math::Rectangle>& source, const Math::Color& tint)
    {
        _items.push_back({ texture, topLeft, topRight, bottomLeft, bottomRight, source, tint });
    }

    void SpriteRenderer::Draw(Texture* texture, const Math::Vector2f& position, const std::optional<Math::Rectangle>& source,
        const Math::Color& tint)
    {
        Math::Size size;
        if (source.has_value())
            size = source.value().Size;
        else
            size = texture->Size();

        const Math::Vector2f fSize = { static_cast<float>(size.Width), static_cast<float>(size.Height) };

        const Math::Vector2f topLeft = position;
        const Math::Vector2f topRight = position + Math::Vector2f(fSize.X, 0);
        const Math::Vector2f bottomLeft = position + Math::Vector2f(0, fSize.Y);
        const Math::Vector2f bottomRight = position + fSize;

        _items.push_back({ texture, topLeft, topRight, bottomLeft, bottomRight, source, tint });
    }

    void SpriteRenderer::Draw(Texture* texture, const Math::Matrixf& matrix, const std::optional<Math::Rectangle>& source,
        const Math::Color& tint)
    {
        Math::Size size;
        if (source.has_value())
            size = source.value().Size;
        else
            size = texture->Size();

        const Math::Vector2f fSize = { static_cast<float>(size.Width), static_cast<float>(size.Height) };

        const Math::Vector2f topLeft = Math::Vector2f::Zero() * matrix;
        const Math::Vector2f topRight = Math::Vector2f(fSize.X, 0) * matrix;
        const Math::Vector2f bottomLeft = Math::Vector2f(0, fSize.Y) * matrix;
        const Math::Vector2f bottomRight = fSize * matrix;

        _items.push_back({ texture, topLeft, topRight, bottomLeft, bottomRight, source, tint });
    }

    void SpriteRenderer::Render(const Math::Matrixf& transform)
    {
        const Math::Rectangle viewport = _device.Viewport();

        CameraMatrices matrices
        {
            // TODO: Make adjust to viewport size
            Math::Matrixf::OrthographicProjection(0, static_cast<float>(viewport.Width()), static_cast<float>(viewport.Height()), 0, -1, 1),
            transform
        };
        _renderable->PushUniformData(0, sizeof(CameraMatrices), &matrices);

        if (_items.empty())
            return;

        uint32_t currentItem = 0;
        Texture* currentTexture = nullptr;
        for (const auto& item : _items)
        {
            if (item.Texture != currentTexture || currentItem >= SP_TEXTUREBATCHER_MAXDRAWS)
            {
                Flush(currentTexture, currentItem);
                currentItem = 0;
            }

            currentTexture = item.Texture;

            const uint32_t vOffset = NumVertices * currentItem;
            const uint32_t iOffset = NumIndices * currentItem;

            const Math::Size texSize = item.Texture->Size();
            const Math::Rectangle source = item.Source.value_or(Math::Rectangle(0, 0, texSize.Width, texSize.Height));

            const float texX = static_cast<float>(source.X()) / static_cast<float>(texSize.Width);
            const float texY = static_cast<float>(source.Y()) / static_cast<float>(texSize.Height);
            const float texW = static_cast<float>(source.Width()) / static_cast<float>(texSize.Width);
            const float texH = static_cast<float>(source.Height()) / static_cast<float>(texSize.Height);

            _vertices[vOffset + 0] = { item.TopLeft, { texX, texY }, item.Tint };
            _vertices[vOffset + 1] = { item.TopRight, { texX + texW, texY }, item.Tint };
            _vertices[vOffset + 2] = { item.BottomRight, { texX + texW, texY + texH }, item.Tint };
            _vertices[vOffset + 3] = { item.BottomLeft, { texX, texY + texH }, item.Tint };

            _indices[iOffset + 0] = 0 + vOffset;
            _indices[iOffset + 1] = 1 + vOffset;
            _indices[iOffset + 2] = 3 + vOffset;
            _indices[iOffset + 3] = 1 + vOffset;
            _indices[iOffset + 4] = 2 + vOffset;
            _indices[iOffset + 5] = 3 + vOffset;

            currentItem++;
        }

        Flush(currentTexture, currentItem);
        _items.clear();
    }

    void SpriteRenderer::Flush(Texture* texture, uint32_t numDraws)
    {
        if (numDraws == 0)
            return;

        const RenderableUpdateInfo updateInfo
        {
            _vertices.data(),
            static_cast<uint32_t>(numDraws * NumVertices * sizeof(Vertex)),
            _indices.data(),
            numDraws * NumIndices
        };
        _renderable->Update(updateInfo);
        _renderable->PushTexture(0, texture);

        _renderable->Draw(numDraws * NumIndices);
    }
}
