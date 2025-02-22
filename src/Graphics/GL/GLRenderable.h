#pragma once

#include "Spritter/Graphics/Renderable.h"

namespace Spritter::Graphics::GL
{
    class GLRenderable : public Renderable
    {
    public:
        explicit GLRenderable(const RenderableDefinition& definition);
        ~GLRenderable();
    };
}