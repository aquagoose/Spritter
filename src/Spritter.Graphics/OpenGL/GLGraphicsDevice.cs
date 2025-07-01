using System.Drawing;
using System.Runtime.InteropServices;
using SDL3;
using Silk.NET.OpenGL;

namespace Spritter.Graphics.OpenGL;

internal sealed class GLGraphicsDevice : GraphicsDevice
{
    private readonly IntPtr _window;
    private readonly IntPtr _context;

    private readonly GL _gl;
    
    public GLGraphicsDevice(IntPtr sdlWindow)
    {
        _window = sdlWindow;

        _context = SDL.GLCreateContext(_window);
        if (_context == IntPtr.Zero)
            throw new Exception($"Failed to create GL context: {SDL.GetError()}");

        if (!SDL.GLMakeCurrent(_window, _context))
            throw new Exception($"Failed to make current: {SDL.GetError()}");
        
        _gl = GL.GetApi(s => Marshal.GetFunctionPointerForDelegate(SDL.GLGetProcAddress(s)));
    }

    public override Shader CreateShader(params ReadOnlySpan<ShaderAttachment> attachments)
    {
        return new GLShader(_gl, in attachments);
    }

    public override Renderable CreateRenderable(in RenderableInfo info)
    {
        return new GLRenderable(_gl, in info);
    }

    public override Texture CreateTexture(byte[] data, Size size, PixelFormat format = PixelFormat.RGBA8)
    {
        return new GLTexture(_gl, data, size, format);
    }

    public override void Clear(Color color)
    {
        _gl.ClearColor(color);
        _gl.Clear(ClearBufferMask.ColorBufferBit);
    }

    public override void Present()
    {
        SDL.GLSetSwapInterval(1);
        SDL.GLSwapWindow(_window);
    }

    public override void Dispose()
    {
        _gl.Dispose();
        SDL.GLDestroyContext(_context);
    }
}