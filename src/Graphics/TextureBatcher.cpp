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
}
