using System.Drawing;
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

    private Texture _currentSwapchainTexture;
    private bool _isInRenderPass;

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
        
        _cl.Begin();
        _currentSwapchainTexture = _swapchain.GetNextTexture();
    }

    public void Clear(Color color)
    {
        if (_isInRenderPass)
            _cl.EndRenderPass();
        
        _isInRenderPass = true;

        Texture texture = _currentSwapchainTexture;

        RenderPassInfo info = new()
        {
            ColorAttachments =
            [
                new ColorAttachmentInfo()
                {
                    Texture = texture,
                    ClearColor = new ColorF(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f),
                    LoadOp = LoadOp.Clear
                }
            ]
        };
        
        _cl.BeginRenderPass(in info);
    }

    public void Present()
    {
        if (_isInRenderPass)
        {
            _cl.EndRenderPass();
            _isInRenderPass = false;
        }
        
        _cl.End();
        _device.ExecuteCommandList(_cl);

        _swapchain.Present();
        
        _cl.Begin();
        _currentSwapchainTexture = _swapchain.GetNextTexture();
    }
    
    public void Dispose()
    {
        _device.WaitForIdle();
        
        _cl.Dispose();
        _swapchain.Dispose();
        _device.Dispose();
        _surface.Dispose();
        _instance.Dispose();
    }
}