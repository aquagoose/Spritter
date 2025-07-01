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

ReadOnlySpan<float> vertices =
[
    -0.5f, +0.5f, 1.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, 0.0f, 1.0f, 0.0f,
    +0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
];

ReadOnlySpan<uint> indices =
[
    0, 1, 3,
    1, 2, 3
];

Renderable renderable = device.CreateRenderable(new RenderableInfo
{
    NumVertices = (uint) vertices.Length,
    NumIndices = (uint) indices.Length,
    Shader = shader,
    VertexSize = 5 * sizeof(float),
    VertexLayout =
    [
        new VertexElement("aPosition", VertexElementType.Float2, 0),
        new VertexElement("aColor", VertexElementType.Float3, 8)
    ]
});

renderable.Update(vertices, indices);

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
        renderable.Draw(6);
        device.Present();
    }
}

renderable.Dispose();
shader.Dispose();
device.Dispose();
window.Dispose();