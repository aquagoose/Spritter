using System.Drawing;
using SDL3;
using Spritter;
using Spritter.Graphics;

const string VertexShader = """
                            #version 330 core

                            in vec2 aPosition;
                            in vec3 aColor;

                            out vec3 frag_Color;

                            void main()
                            {
                                gl_Position = vec4(aPosition, 0.0, 1.0);
                                frag_Color = aColor;
                            }
                            """;

const string PixelShader = """
                           #version 330 core

                           in vec3 frag_Color;

                           out vec4 out_Color;

                           void main()
                           {
                               out_Color = vec4(frag_Color, 1.0);
                           }
                           """;

Window window = new Window("Tests.Graphics", new Size(1280, 720));
GraphicsDevice device = GraphicsDevice.Create(window.Handle, Renderer.OpenGL);

Shader shader = device.CreateShader(new ShaderAttachment(ShaderStage.Vertex, VertexShader, "main"),
    new ShaderAttachment(ShaderStage.Pixel, PixelShader, "main"));

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

shader.Dispose();
device.Dispose();
window.Dispose();