using Silk.NET.OpenGL;

namespace Spritter.Graphics.OpenGL;

internal sealed class GLShader : Shader
{
    private readonly GL _gl;
    
    public readonly uint Program;
    
    public GLShader(GL gl, in ReadOnlySpan<ShaderAttachment> attachments)
    {
        _gl = gl;

        List<uint> shaders = [];

        Program = _gl.CreateProgram();
        
        foreach (ShaderAttachment attachment in attachments)
        {
            ShaderType type = attachment.Stage switch
            {
                ShaderStage.Vertex => ShaderType.VertexShader,
                ShaderStage.Pixel => ShaderType.FragmentShader,
                _ => throw new ArgumentOutOfRangeException()
            };

            uint shader = _gl.CreateShader(type);
            shaders.Add(shader);
            _gl.ShaderSource(shader, attachment.Code);
            _gl.CompileShader(shader);

            _gl.GetShader(shader, GLEnum.CompileStatus, out int compStatus);
            if (compStatus != (int) GLEnum.True)
                throw new Exception($"Failed to compile {attachment.Stage} shader: {_gl.GetShaderInfoLog(shader)}");
            
            _gl.AttachShader(Program, shader);
        }
        
        _gl.LinkProgram(Program);

        _gl.GetProgram(Program, GLEnum.LinkStatus, out int linkStatus);
        if (linkStatus != (int) GLEnum.True)
            throw new Exception($"Failed to link program: {_gl.GetProgramInfoLog(Program)}");

        foreach (uint shader in shaders)
        {
            _gl.DetachShader(Program, shader);
            _gl.DeleteShader(shader);
        }
    }
    
    public override void Dispose()
    {
        _gl.DeleteProgram(Program);
    }
}