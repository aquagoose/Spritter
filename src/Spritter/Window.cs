using System.Drawing;
using grabs.Core;
using grabs.Windowing;
using grabs.Windowing.Events;

namespace Spritter;

public class Window : IDisposable
{
    public event OnClose Close = delegate { };
    
    internal readonly grabs.Windowing.Window GrabsWindow;

    public Size Size
    {
        get
        {
            Size2D size = GrabsWindow.SizeInPixels;
            return new Size((int) size.Width, (int) size.Height);
        }
        set => GrabsWindow.Size = new Size2D((uint) value.Width, (uint) value.Height);
    }

    public Window(string title, Size size)
    {
        WindowInfo info = new WindowInfo(new Size2D((uint) size.Width, (uint) size.Height), title);

        GrabsWindow = new grabs.Windowing.Window(info);
    }

    internal void ProcessEvents()
    {
        while (GrabsWindow.PollEvent(out Event winEvent))
        {
            switch (winEvent.Type)
            {
                case EventType.Close:
                    Close();
                    break;
                case EventType.None:
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }
    }

    internal void UnregisterEvents()
    {
        Close = delegate { };
    }
    
    public void Dispose()
    {
        UnregisterEvents();
        GrabsWindow.Dispose();
    }

    public delegate void OnClose();
}