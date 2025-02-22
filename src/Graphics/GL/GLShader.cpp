#include "GLShader.h"

#include <vector>
#include <stdexcept>

namespace Spritter::Graphics::GL
{
    GLShader::GLShader(ShaderAttachment* attachments, int numAttachments)
    {
        Program = glCreateProgram();

        std::vector<GLuint> shaders;

        for (int i = 0; i < numAttachments; i++)
        {
            GLenum shaderType;
            switch (attachments[i].Stage)
            {
                case ShaderStage::Vertex:
                    shaderType = GL_VERTEX_SHADER;
                    break;
                case ShaderStage::Pixel:
                    shaderType = GL_FRAGMENT_SHADER;
                    break;
                default:
                    throw std::runtime_error("Invalid shader stage.");
            }

            GLuint shader = glCreateShader(shaderType);
            shaders.push_back(shader);

            auto shaderSource = attachments[i].Code.c_str();
            auto length = static_cast<GLint>(attachments[i].Code.length());
            glShaderSource(shader, 1, &shaderSource, &length);

            glCompileShader(shader);

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

            if (!status)
            {
                GLint bufferSize;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufferSize);
                std::string errorString;
                errorString.resize(bufferSize);
                glGetShaderInfoLog(shader, bufferSize, nullptr, errorString.data());

                throw std::runtime_error("Failed to compile shader: " + errorString);
            }

            glAttachShader(Program, shader);
        }

        glLinkProgram(Program);

        GLint status;
        glGetProgramiv(Program, GL_LINK_STATUS, &status);

        if (!status)
        {
            GLint bufferSize;
            glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &bufferSize);
            std::string errorString;
            errorString.resize(bufferSize);
            glGetProgramInfoLog(Program, bufferSize, nullptr, errorString.data());
        }

        for (auto shader : shaders)
        {
            glDetachShader(Program, shader);
            glDeleteShader(shader);
        }
    }

    GLShader::~GLShader()
    {
        glDeleteProgram(Program);
    }
}
