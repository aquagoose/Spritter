namespace Spritter;

public abstract class Game : IDisposable
{
    private bool _isRunning;

    public readonly Window Window;
    
    public Game(in GameOptions options)
    {
        Window = new Window(options.Name, options.Size);
        Window.Close += Close;
    }

    public void Run()
    {
        if (_isRunning)
            return;

        _isRunning = true;

        while (_isRunning)
        {
            Window.ProcessEvents();
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