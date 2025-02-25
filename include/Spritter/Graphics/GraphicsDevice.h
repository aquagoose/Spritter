#pragma once

#include <memory>

#include "Renderable.h"
#include "Shader.h"
#include "../Math/Color.h"

namespace Spritter::Graphics
{
    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        virtual bool VSyncMode() = 0;
        virtual void SetVSyncMode(bool vsync) = 0;

        virtual std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) = 0;

        virtual std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) = 0;

        virtual void Clear(const Math::Color& color) = 0;

        virtual void Present() = 0;
    };
}
