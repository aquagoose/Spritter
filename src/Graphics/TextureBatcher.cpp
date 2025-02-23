#include "Spritter/Graphics/TextureBatcher.h"

const char* TBVertexShader = R"(
#version 330 core

in vec2 aPosition;
in vec2 aTexCoord;
in vec4 aTint;

out vec2 frag_TexCoord;
out vec4 frag_Tint;

void main()
{
    gl_Position = vec4(aPosition, 0.0, 1.0);
    frag_TexCoord = aTexCoord;
    frag_Tint = aTint;
}
)";

const char* TBPixelShader = R"(
#version 330 core

in vec2 frag_TexCoord;
in vec4 frag_Tint;

out vec4 out_Color;

void main()
{
    out_Color = frag_Tint;
}
)";

namespace Spritter::Graphics
{
    TextureBatcher::TextureBatcher(GraphicsDevice* device)
    {
        ShaderAttachment attachments[]
        {
            { ShaderStage::Vertex, TBVertexShader },
            { ShaderStage::Pixel, TBPixelShader }
        };
        _defaultShader = device->CreateShader(attachments, 2);

        ShaderAttribute attributes[]
        {
            { "aPosition", AttributeType::Float2, offsetof(Vertex, Position) },
            { "aTexCoord", AttributeType::Float2, offsetof(Vertex, TexCoord) },
            { "aTint", AttributeType::Float4, offsetof(Vertex, Tint) }
        };

        RenderableDefinition definition
        {
            nullptr,
            MaxVertices,
            nullptr,
            MaxIndices,
            _defaultShader.get(),
            attributes,
            3,
            sizeof(Vertex),
            true
        };
        _renderable = device->CreateRenderable(definition);
    }

    void TextureBatcher::Draw(const Vector2f& topLeft, const Vector2f& topRight, const Vector2f& bottomLeft,
        const Vector2f& bottomRight, const Color& tint)
    {
        _items.push_back({ topLeft, topRight, bottomLeft, bottomRight, tint });
    }

    void TextureBatcher::Render()
    {
        if (_items.empty())
            return;

        uint32_t currentItem = 0;
        for (const auto& item : _items)
        {
            if (currentItem >= SP_TEXTUREBATCHER_MAXDRAWS)
            {
                Flush(currentItem);
                currentItem = 0;
            }

            const uint32_t vOffset = NumVertices * currentItem;
            const uint32_t iOffset = NumIndices * currentItem;

            _vertices[vOffset + 0] = { item.TopLeft, { 0, 0 }, item.Tint };
            _vertices[vOffset + 1] = { item.TopRight, { 1, 0 }, item.Tint };
            _vertices[vOffset + 2] = { item.BottomRight, { 1, 1 }, item.Tint };
            _vertices[vOffset + 3] = { item.BottomLeft, { 0, 1 }, item.Tint };

            _indices[iOffset + 0] = 0 + vOffset;
            _indices[iOffset + 1] = 1 + vOffset;
            _indices[iOffset + 2] = 3 + vOffset;
            _indices[iOffset + 3] = 1 + vOffset;
            _indices[iOffset + 4] = 2 + vOffset;
            _indices[iOffset + 5] = 3 + vOffset;

            currentItem++;
        }

        Flush(currentItem);
        _items.clear();
    }

    void TextureBatcher::Flush(uint32_t numDraws)
    {
        if (numDraws == 0)
            return;

        RenderableUpdateInfo updateInfo
        {
            _vertices.data(),
            static_cast<uint32_t>(numDraws * NumVertices * sizeof(Vertex)),
            _indices.data(),
            numDraws * NumIndices
        };
        _renderable->Update(updateInfo);

        _renderable->Draw(numDraws * NumIndices);
    }
}
