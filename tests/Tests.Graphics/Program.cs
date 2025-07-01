using System.Drawing;
using SDL3;
using Spritter;

Window window = new Window("Tests.Graphics", new Size(1280, 720));

bool alive = true;
while (alive)
{
    while (SDL.PollEvent(out SDL.Event winEvent))
    {
        switch ((SDL.EventType) winEvent.Type)
        {
            case SDL.EventType.WindowCloseRequested:
                alive = false;
                break;
        }
    }
}

window.Dispose();