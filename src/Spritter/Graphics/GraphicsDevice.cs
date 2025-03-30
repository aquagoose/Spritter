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
            Size = new Size2D(1280, 720),
            PresentMode = PresentMode.Fifo,
            NumBuffers = 2
        };

        _swapchain = _device.CreateSwapchain(in swapchainInfo);
    }
    
    public void Dispose()
    {
        _device.Dispose();
        _surface.Dispose();
        _instance.Dispose();
    }
}