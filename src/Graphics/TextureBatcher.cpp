#include "Spritter/Graphics/TextureBatcher.h"

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
    Matrixf Projection;
    Matrixf Transform;
};

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
            MaxVertices,
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
        _renderable = device->CreateRenderable(definition);
    }

    void TextureBatcher::Draw(Texture* texture, const Vector2f& topLeft, const Vector2f& topRight,
                              const Vector2f& bottomLeft, const Vector2f& bottomRight,
                              const std::optional<Rectangle>& source, const Color& tint)
    {
        _items.push_back({ texture, topLeft, topRight, bottomLeft, bottomRight, source, tint });
    }

    void TextureBatcher::Draw(Texture* texture, const Vector2f& position, const std::optional<Rectangle>& source,
        const Color& tint)
    {
        Size size;
        if (source.has_value())
            size = source.value().Size;
        else
            size = texture->Size();

        const Vector2f topLeft = position;
        const Vector2f topRight = position + Vector2f(static_cast<float>(size.Width), 0);
        const Vector2f bottomLeft = position + Vector2f(0, static_cast<float>(size.Height));
        const Vector2f bottomRight = position + Vector2f(static_cast<float>(size.Width), static_cast<float>(size.Height));

        _items.push_back({ texture, topLeft, topRight, bottomLeft, bottomRight, source, tint });
    }

    void TextureBatcher::Draw(Texture* texture, const Vector2f& position)
    {
        Draw(texture, position, {}, Color::White());
    }

    void TextureBatcher::Render()
    {
        CameraMatrices matrices
        {
            Matrixf::OrthographicProjection(0, 1280, 720, 0, -1, 1),
            Matrixf::Identity()
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

            const Size texSize = item.Texture->Size();
            const Rectangle source = item.Source.value_or(Rectangle(0, 0, texSize.Width, texSize.Height));

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

    void TextureBatcher::Flush(Texture* texture, uint32_t numDraws)
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
