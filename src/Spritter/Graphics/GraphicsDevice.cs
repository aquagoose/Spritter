using grabs.Core;
using grabs.Graphics;
using grabs.Graphics.D3D11;
using grabs.Graphics.Vulkan;

namespace Spritter.Graphics;

public class GraphicsDevice : IDisposable
{
    private readonly Instance _instance;
    private readonly Surface _surface;
    private readonly Device _device;
    private readonly Swapchain _swapchain;
    private readonly CommandList _cl;

    public GraphicsDevice(string appName, Window window)
    {
        if (OperatingSystem.IsWindows())
            Instance.RegisterBackend<D3D11Backend>();
        Instance.RegisterBackend<VulkanBackend>();

        InstanceInfo instanceInfo = new()
        {
            AppName = appName,
#if DEBUG
            Debug = true
#endif
        };

        _instance = Instance.Create(in instanceInfo);
        _surface = window.GrabsWindow.CreateSurface(_instance);

        _device = _instance.CreateDevice(_surface);

        SwapchainInfo swapchainInfo = new()
        {
            Surface = _surface,
            Format = _surface.GetOptimalSwapchainFormat(_device.Adapter),
            Size = window.GrabsWindow.SizeInPixels,
            PresentMode = PresentMode.Fifo,
            NumBuffers = 2
        };

        _swapchain = _device.CreateSwapchain(in swapchainInfo);

        _cl = _device.CreateCommandList();
    }

    public void Present()
    {
        _swapchain.Present();
    }
    
    public void Dispose()
    {
        _cl.Dispose();
        _swapchain.Dispose();
        _device.Dispose();
        _surface.Dispose();
        _instance.Dispose();
    }
}