#pragma once

#include <memory>
#include <string>

#include "Renderable.h"
#include "Shader.h"
#include "Texture.h"
#include "../Math/Color.h"

namespace Spritter::Graphics
{
    enum class FullscreenMode
    {
        Windowed,
        BorderlessFullscreen,
        //ExclusiveFullscreen
    };

    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        virtual bool VSyncMode() = 0;
        virtual void SetVSyncMode(bool vsync) = 0;

        virtual Graphics::FullscreenMode FullscreenMode() = 0;
        virtual void SetFullscreenMode(Graphics::FullscreenMode mode) = 0;

        virtual Math::Rectangle Viewport() = 0;
        virtual void SetViewport(const Math::Rectangle& viewport) = 0;

        virtual std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) = 0;

        virtual std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) = 0;

        virtual std::unique_ptr<Texture> CreateTexture(uint32_t width, uint32_t height, PixelFormat format, void* data) = 0;

        std::unique_ptr<Texture> CreateTexture(const std::string& path);

        virtual void BeginRendering(const Math::Color& color) = 0;

        virtual void EndRendering() = 0;

        virtual void Present() = 0;

        virtual void ResizeSwapchain(const Math::Size& size) = 0;
    };
}
