using System.Drawing;
using System.Numerics;
using SDL3;
using Spritter;
using Spritter.Graphics;

const string VertexShader = """
                            #version 330 core

                            in vec2 aPosition;
                            in vec2 aTexCoord;

                            out vec2 frag_TexCoord;
                            
                            layout (std140) uniform uTest
                            {
                                mat4 Test;
                            };

                            void main()
                            {
                                gl_Position = Test * vec4(aPosition, 0.0, 1.0);
                                frag_TexCoord = aTexCoord;
                            }
                            """;

const string PixelShader = """
                           #version 330 core

                           in vec2 frag_TexCoord;

                           out vec4 out_Color;
                           
                           uniform sampler2D uTexture;

                           void main()
                           {
                               out_Color = texture(uTexture, frag_TexCoord);
                           }
                           """;

Window window = new Window("Tests.Graphics", new Size(1280, 720));
GraphicsDevice device = GraphicsDevice.Create(window.Handle, Renderer.OpenGL);

Shader shader = device.CreateShader(new ShaderAttachment(ShaderStage.Vertex, VertexShader, "main"),
    new ShaderAttachment(ShaderStage.Pixel, PixelShader, "main"));

Texture texture = device.CreateTexture("/home/aqua/Pictures/BAGELMIP.png");

ReadOnlySpan<float> vertices =
[
    -0.5f, +0.5f, 0.0f, 0.0f,
    +0.5f, +0.5f, 1.0f, 0.0f,
    +0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f
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
    VertexSize = 4 * sizeof(float),
    VertexLayout =
    [
        new VertexElement("aPosition", VertexElementType.Float2, 0),
        new VertexElement("aTexCoord", VertexElementType.Float2, 8)
    ],
    Uniforms =
    [
        new Uniform(UniformType.ConstantBuffer, "uTest", 64),
        new Uniform(UniformType.Texture, "uTexture")
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
        
        renderable.PushUniform("uTest", Matrix4x4.CreateRotationZ(1));
        renderable.PushTexture("uTexture", texture);
        renderable.Draw(6);
        
        device.Present();
    }
}

renderable.Dispose();
texture.Dispose();
shader.Dispose();
device.Dispose();
window.Dispose();