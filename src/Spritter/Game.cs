using Pie;
using Pie.Windowing;
using Pie.Windowing.Events;

namespace Spritter;

public abstract class Game : IDisposable
{
    private bool _isRunning;

    public readonly Window Window;
    
    public Game(in GameOptions options)
    {
        Window = new WindowBuilder()
            .Title(options.Name)
            .Size(options.Size.Width, options.Size.Height)
            .Build(out GraphicsDevice device);
    }

    public void Run()
    {
        if (_isRunning)
            return;

        _isRunning = true;

        while (_isRunning)
        {
            while (Window.PollEvent(out IWindowEvent winEvent))
            {
                switch (winEvent)
                {
                    case QuitEvent:
                        _isRunning = false;
                        break;
                }
            }
        }
    }

    public void Close()
    {
        _isRunning = false;
    }
    
    public virtual void Dispose()
    {
        Window.Dispose();
    }
}