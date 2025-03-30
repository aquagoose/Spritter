using Pie;

namespace Spritter;

public class Game : IDisposable
{
    public readonly Window Window;
    
    public Game(in GameOptions options)
    {
        GraphicsApi api = GraphicsDevice.GetBestApiForPlatform();

        Window = new Window(options.Name, options.Size, api);
    }
    
    public virtual void Dispose()
    {
        Window.Dispose();
    }
}