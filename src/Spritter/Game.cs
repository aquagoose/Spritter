using grabs.Core;
using grabs.Windowing;
using grabs.Windowing.Events;

namespace Spritter;

public abstract class Game : IDisposable
{
    private bool _alive;
    
    public required Window Window;

    protected virtual void Initialize() { }
    
    protected virtual void Update(float dt) { }
    
    protected virtual void Draw() { }

    public void Run(in GameOptions options)
    {
        WindowInfo windowInfo =
            new WindowInfo(new Size2D((uint) options.Size.Width, (uint) options.Size.Height), options.Name);

        Window = new Window(in windowInfo);

        _alive = true;
        while (_alive)
        {
            while (Window.PollEvent(out Event winEvent))
            {
                switch (winEvent.Type)
                {
                    case EventType.Close:
                        _alive = false;
                        break;
                }
            }
        }
    }
    
    public void Dispose()
    {
        Window.Dispose();
    }
}