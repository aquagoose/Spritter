using Spritter.Graphics;

namespace Spritter;

public abstract class Game : IDisposable
{
    private bool _isRunning;

    public readonly Window Window;

    public readonly GraphicsDevice GraphicsDevice;
    
    public Game(in GameOptions options)
    {
        Window = new Window(options.Name, options.Size);
        Window.Close += Close;

        GraphicsDevice = new GraphicsDevice(options.Name, Window);
    }

    public void Run()
    {
        if (_isRunning)
            return;

        _isRunning = true;

        while (_isRunning)
        {
            Window.ProcessEvents();
            GraphicsDevice.Present();
        }
    }

    public void Close()
    {
        _isRunning = false;
    }
    
    public virtual void Dispose()
    {
        GraphicsDevice.Dispose();
        Window.Dispose();
    }
}