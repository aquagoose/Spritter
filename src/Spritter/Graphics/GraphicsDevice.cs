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
    private readonly Swapchain _swapchain;

    private GrabsTexture _currentSwapchainTexture;
    private bool _isInRenderPass;

    internal readonly Device Device;
    internal readonly CommandList CommandList;
    internal GraphicsState CurrentState;

    public GraphicsDevice(string appName, Window window)
    {
        CurrentState = new GraphicsState();
        
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

        Device = _instance.CreateDevice(_surface);

        SwapchainInfo swapchainInfo = new()
        {
            Surface = _surface,
            Format = _surface.GetOptimalSwapchainFormat(Device.Adapter),
            Size = window.GrabsWindow.SizeInPixels,
            PresentMode = PresentMode.Fifo,
            NumBuffers = 2
        };

        _swapchain = Device.CreateSwapchain(in swapchainInfo);

        CommandList = Device.CreateCommandList();
        
        CommandList.Begin();
        _currentSwapchainTexture = _swapchain.GetNextTexture();
        CurrentState.RenderPassFormat = _swapchain.SwapchainFormat;
    }

    public Shader CreateShader(params ReadOnlySpan<ShaderAttachment> attachments)
    {
        return new Shader(Device, in attachments);
    }

    public Texture CreateTexture(Size size, byte[] data, PixelFormat format = PixelFormat.R8G8B8A8_UNorm)
    {
        return new Texture(Device, size, data.AsSpan(), format);
    }

    public Renderable CreateRenderable(in RenderableInfo info)
    {
        return new Renderable(this, in info);
    }

    public void Clear(Color color)
    {
        if (_isInRenderPass)
            CommandList.EndRenderPass();
        
        _isInRenderPass = true;

        GrabsTexture texture = _currentSwapchainTexture;

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
        
        CommandList.SetViewport(new Viewport(0, 0, _swapchain.Size.Width, _swapchain.Size.Height));
        
        CommandList.BeginRenderPass(in info);
    }

    public void Present()
    {
        if (_isInRenderPass)
        {
            CommandList.EndRenderPass();
            _isInRenderPass = false;
        }
        
        CommandList.End();
        Device.ExecuteCommandList(CommandList);

        _swapchain.Present();
        
        CommandList.Begin();
        _currentSwapchainTexture = _swapchain.GetNextTexture();
    }
    
    public void Dispose()
    {
        Device.WaitForIdle();
        
        CommandList.Dispose();
        _swapchain.Dispose();
        Device.Dispose();
        _surface.Dispose();
        _instance.Dispose();
    }
}