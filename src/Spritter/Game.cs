using SDL3;
using Spritter.Graphics;

namespace Spritter;

public abstract class Game : IDisposable
{
    private Window _window = null!;
    private GraphicsDevice _device = null!;

    private bool _isRunning;

    public Window Window => _window;

    public GraphicsDevice GraphicsDevice => _device;

    protected virtual void Initialize() { }

    protected virtual void Update(float dt) { }

    protected virtual void Draw() { }

    public void Run(in GameInfo info)
    {
        _window = new Window(info.Name, info.Size);
        _device = GraphicsDevice.Create(_window.Handle, Renderer.OpenGL);
        
        Initialize();

        _isRunning = true;

        while (_isRunning)
        {
            while (SDL.PollEvent(out SDL.Event winEvent))
            {
                switch ((SDL.EventType) winEvent.Type)
                {
                    case SDL.EventType.WindowCloseRequested:
                        _isRunning = false;
                        break;
                }
            }
            
            Update(1f / 60f);
            Draw();
            
            _device.Present();
        }
    }
    
    public virtual void Dispose()
    {
        _device.Dispose();
        _window.Dispose();
    }
}