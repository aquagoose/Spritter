using System.Drawing;
using Pie;
using SDL;
using static SDL.SDL3;

namespace Spritter;

public unsafe class Window : IDisposable
{
    private SDL_Window* _window;
    private SDL_GLContextState* _glContext;
    
    public Window(string title, Size size, GraphicsApi api)
    {
        if (!SDL_Init(SDL_InitFlags.SDL_INIT_VIDEO))
            throw new Exception($"Failed to initialize SDL: {SDL_GetError()}");

        SDL_WindowFlags flags = 0;

        switch (api)
        {
            case GraphicsApi.OpenGL:
            case GraphicsApi.OpenGLES:
                flags |= SDL_WindowFlags.SDL_WINDOW_OPENGL;
                SDL_GL_SetAttribute(SDL_GLAttr.SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                SDL_GL_SetAttribute(SDL_GLAttr.SDL_GL_CONTEXT_MINOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GLAttr.SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                break;
            case GraphicsApi.D3D11:
                break;
            case GraphicsApi.Null:
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(api), api, null);
        }

        _window = SDL_CreateWindow(title, size.Width, size.Height, flags);

        if (_window == null)
            throw new Exception($"Failed to create window: {SDL_GetError()}");

        if (api is GraphicsApi.OpenGL or GraphicsApi.OpenGLES)
        {
            _glContext = SDL_GL_CreateContext(_window);
            if (_glContext == null)
                throw new Exception($"Failed to create GL context: {SDL_GetError()}");
            
            SDL_GL_MakeCurrent(_window, _glContext);
        }
    }

    public void Dispose()
    {
        if (_glContext != null)
            SDL_GL_DestroyContext(_glContext);
        
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }
}