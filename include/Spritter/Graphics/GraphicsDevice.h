#pragma once

#include <memory>
#include <string>

#include "Renderable.h"
#include "../Math/Color.h"
#include "TextureBatcher.h"

namespace Spritter::Graphics
{
    enum class ShaderStage
    {
        Vertex,
        Pixel
    };

    struct ShaderAttachment
    {
        ShaderStage Stage;
        std::string Code;
    };

    class Shader {};

    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        virtual std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) = 0;

        virtual std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) = 0;

        virtual void Clear(const Math::Color& color) = 0;

        virtual void Present() = 0;
    };
}
