#pragma once

#include <memory>

#include "Renderable.h"
#include "../Math/Color.h"
#include "TextureBatcher.h"

namespace Spritter::Graphics
{
    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = 0;

        virtual std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) = 0;

        virtual void Clear(const Math::Color& color) = 0;

        virtual void Present() = 0;
    };
}
