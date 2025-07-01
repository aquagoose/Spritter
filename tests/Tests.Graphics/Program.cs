using System.Drawing;
using SDL3;
using Spritter;
using Spritter.Graphics;

Window window = new Window("Tests.Graphics", new Size(1280, 720));
GraphicsDevice device = GraphicsDevice.Create(window.Handle, Renderer.OpenGL);

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
        
        device.Clear(Color.CornflowerBlue);
        device.Present();
    }
}

device.Dispose();
window.Dispose();