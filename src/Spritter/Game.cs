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

    protected virtual void Initialize() { }
    protected virtual void Update(float dt) { }
    protected virtual void Draw() { }

    public void Run()
    {
        if (_isRunning)
            return;
        
        Initialize();

        _isRunning = true;

        while (_isRunning)
        {
            Window.ProcessEvents();
            
            Update(1.0f / 60f);
            Draw();
            
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