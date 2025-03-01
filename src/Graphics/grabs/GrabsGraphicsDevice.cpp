#include "GrabsGraphicsDevice.h"

#include <stdexcept>
#include <string>

#define CHECK_RESULT(Operation) {\
    GsResult res = Operation;\
    if (res != GS_RESULT_OK)\
        throw std::runtime_error("grabs operation failed with result: " + std::string(gsResultToString(res)));\
}

namespace Spritter::Graphics::Grabs
{
    GrabsGraphicsDevice::GrabsGraphicsDevice(SDL_Window* window, const Math::Size& windowSize)
    {
        _window = window;

        gsInit();

        GsInstanceInfo instanceInfo
        {
            "Spritter",
            GS_BACKEND_UNKNOWN,
            true
        };

        CHECK_RESULT(gsCreateInstance(&instanceInfo, &_instance));

        GsSurfaceInfo surfaceInfo;
        SDL_PropertiesID properties = SDL_GetWindowProperties(window);
#if defined(SDL_PLATFORM_WIN32)
#error "Not yet implemented"
#elif defined(SDL_PLATFORM_LINUX)
        const auto driver = SDL_GetCurrentVideoDriver();
        if (SDL_strcmp(driver, "x11") == 0)
        {
            Display* display = (Display*) SDL_GetPointerProperty(properties, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);
            Window xwindow = (Window) SDL_GetNumberProperty(properties, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
            surfaceInfo.type = GS_SURFACE_TYPE_XLIB;
            surfaceInfo.display.xlib = display;
            surfaceInfo.window.xlib = xwindow;
        }
        else if (SDL_strcmp(driver, "wayland") == 0)
        {
            struct wl_display* display = (struct wl_display*) SDL_GetPointerProperty(properties, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
            struct wl_surface* surface = (struct wl_surface*) SDL_GetPointerProperty(properties, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
            surfaceInfo.type = GS_SURFACE_TYPE_WAYLAND;
            surfaceInfo.display.wayland = display;
            surfaceInfo.window.wayland = surface;
        }
#endif

        CHECK_RESULT(gsInstanceCreateSurface(_instance, &surfaceInfo, &_surface));
        CHECK_RESULT(gsInstanceCreateDevice(_instance, _surface, nullptr, &_device));

        GsSwapchainInfo swapchainInfo
        {
            _surface,
            { static_cast<uint32_t>(windowSize.Width), static_cast<uint32_t>(windowSize.Height) },
            GS_FORMAT_B8G8R8A8_UNORM,
            GS_PRESENT_MODE_FIFO,
            2
        };
        CHECK_RESULT(gsDeviceCreateSwapchain(_device, &swapchainInfo, &_swapchain));

        CHECK_RESULT(gsDeviceCreateCommandList(_device, &_commandList))

        CHECK_RESULT(gsSwapchainGetNextTexture(_swapchain, &_currentSwapchainTexture));

        CHECK_RESULT(gsBeginCommandList(_commandList));
    }

    GrabsGraphicsDevice::~GrabsGraphicsDevice()
    {
        gsDestroySwapchain(_swapchain);
        gsDestroyDevice(_device);
        gsDestroySurface(_surface);
        gsDestroyInstance(_instance);
    }

    bool GrabsGraphicsDevice::VSyncMode()
    {
        return false;
    }

    void GrabsGraphicsDevice::SetVSyncMode(bool vsync)
    {
    }

    Graphics::FullscreenMode GrabsGraphicsDevice::FullscreenMode()
    {
        return FullscreenMode::Windowed;
    }

    void GrabsGraphicsDevice::SetFullscreenMode(Graphics::FullscreenMode mode)
    {
    }

    Math::Rectangle GrabsGraphicsDevice::Viewport()
    {
        return { 0, 0, 0, 0 };
    }

    void GrabsGraphicsDevice::SetViewport(const Math::Rectangle& viewport)
    {
    }

    std::unique_ptr<Shader> GrabsGraphicsDevice::CreateShader(ShaderAttachment* attachments, int numAttachments)
    {
        return nullptr;
    }

    std::unique_ptr<Renderable> GrabsGraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return nullptr;
    }

    std::unique_ptr<Texture> GrabsGraphicsDevice::CreateTexture(uint32_t width, uint32_t height, PixelFormat format,
        void* data)
    {
        return nullptr;
    }

    void GrabsGraphicsDevice::Clear(const Math::Color& color)
    {
        if (_isInRenderPass)
            gsEndRenderPass(_commandList);

        GsColorAttachmentInfo colorAttachment
        {
            _currentSwapchainTexture,
            { color.R, color.G, color.B, color.A },
            GS_LOAD_OP_CLEAR
        };

        GsRenderPassInfo passInfo
        {
            1,
            &colorAttachment
        };

        gsBeginRenderPass(_commandList, &passInfo);
        _isInRenderPass = true;
    }

    void GrabsGraphicsDevice::Present()
    {
        if (_isInRenderPass)
            gsEndRenderPass(_commandList);
        _isInRenderPass = false;

        gsEndCommandList(_commandList);
        CHECK_RESULT(gsDeviceExecuteCommandList(_device, _commandList));

        CHECK_RESULT(gsSwapchainPresent(_swapchain));
        CHECK_RESULT(gsSwapchainGetNextTexture(_swapchain, &_currentSwapchainTexture));
        CHECK_RESULT(gsBeginCommandList(_commandList));
    }

    void GrabsGraphicsDevice::ResizeSwapchain(const Math::Size& size)
    {
    }
}
