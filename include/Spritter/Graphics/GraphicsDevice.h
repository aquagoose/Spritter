#pragma once

namespace Spritter::Graphics
{
    class GraphicsDevice
    {
    public:
        virtual void Clear() = 0;

        virtual void Present() = 0;
    };
}