using System.Drawing;
using SDL3;

namespace Spritter;

public sealed class Window : IDisposable
{
    private readonly IntPtr _window;

    public IntPtr Handle => _window;

    public Window(string title, Size size)
    {
        if (!SDL.Init(SDL.InitFlags.Video | SDL.InitFlags.Events))
            throw new Exception($"Failed to initialize SDL: {SDL.GetError()}");

        SDL.GLSetAttribute(SDL.GLAttr.ContextMajorVersion, 3);
        SDL.GLSetAttribute(SDL.GLAttr.ContextMinorVersion, 3);
        SDL.GLSetAttribute(SDL.GLAttr.ContextProfileMask, (int) SDL.GLProfile.Core);
        
        _window = SDL.CreateWindow(title, size.Width, size.Height, SDL.WindowFlags.OpenGL);

        if (_window == IntPtr.Zero)
            throw new Exception($"Failed to create window: {SDL.GetError()}");
    }
    
    public void Dispose()
    {
        SDL.DestroyWindow(_window);
        SDL.Quit();
    }
}