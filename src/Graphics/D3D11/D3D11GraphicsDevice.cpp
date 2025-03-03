#include "D3D11GraphicsDevice.h"

#include "D3D11Utils.h"

namespace Spritter::Graphics::D3D11
{
    D3D11GraphicsDevice::D3D11GraphicsDevice(SDL_Window* window)
    {
        int w, h;
        SDL_GetWindowSizeInPixels(window, &w, &h);

        HWND hwnd = (HWND) SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);

        DXGI_SWAP_CHAIN_DESC swapchainDesc{};
        swapchainDesc.OutputWindow = hwnd;
        swapchainDesc.Windowed = TRUE;
        swapchainDesc.BufferCount = 2;
        swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapchainDesc.BufferDesc.Width = static_cast<UINT>(w);
        swapchainDesc.BufferDesc.Height = static_cast<UINT>(h);
        swapchainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapchainDesc.SampleDesc.Count = 1;
        swapchainDesc.SampleDesc.Quality = 0;
        swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapchainDesc.Flags = 0;

        auto flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        constexpr D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };
        D3D11_CHECK(
            D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, featureLevels, 1,
                D3D11_SDK_VERSION, &swapchainDesc, &_swapchain, &_device, nullptr, &_context));

        D3D11_CHECK(_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &_swapchainTexture));

        D3D11_CHECK(_device->CreateRenderTargetView(_swapchainTexture, nullptr, &_swapchainTarget));
    }

    D3D11GraphicsDevice::~D3D11GraphicsDevice()
    {
        _swapchainTarget->Release();
        _swapchainTexture->Release();
        _swapchain->Release();
        _context->Release();
        _device->Release();
    }

    bool D3D11GraphicsDevice::VSyncMode()
    {
        return true;
    }

    void D3D11GraphicsDevice::SetVSyncMode(bool vsync)
    {
    }

    Graphics::FullscreenMode D3D11GraphicsDevice::FullscreenMode()
    {
        return FullscreenMode::Windowed;
    }

    void D3D11GraphicsDevice::SetFullscreenMode(Graphics::FullscreenMode mode)
    {
    }

    Math::Rectangle D3D11GraphicsDevice::Viewport()
    {
        return {};
    }

    void D3D11GraphicsDevice::SetViewport(const Math::Rectangle& viewport)
    {
    }

    std::unique_ptr<Shader> D3D11GraphicsDevice::CreateShader(ShaderAttachment* attachments, int numAttachments)
    {
        return nullptr;
    }

    std::unique_ptr<Renderable> D3D11GraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return nullptr;
    }

    std::unique_ptr<Texture> D3D11GraphicsDevice::CreateTexture(uint32_t width, uint32_t height, PixelFormat format,
        void* data)
    {
        return nullptr;
    }

    void D3D11GraphicsDevice::Clear(const Math::Color& color)
    {
        const float clearColor[] = { color.R, color.G, color.B, color.A };
        _context->ClearRenderTargetView(_swapchainTarget, clearColor);
    }

    void D3D11GraphicsDevice::Present()
    {
        D3D11_CHECK(_swapchain->Present(1, 0));
    }

    void D3D11GraphicsDevice::ResizeSwapchain(const Math::Size& size)
    {
    }
}
