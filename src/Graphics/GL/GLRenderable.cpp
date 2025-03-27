#include "GLRenderable.h"

#include <stdexcept>

#include "GLTexture.h"

namespace Spritter::Graphics::GL
{
    GLRenderable::GLRenderable(const RenderableDefinition& definition)
    {
        _stride = definition.ShaderStride;
        _shader = dynamic_cast<GLShader*>(definition.Shader);

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        const auto usage = definition.Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, definition.NumVertices, definition.Vertices, usage);

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(definition.NumIndices * sizeof(uint32_t)), definition.Indices, usage);

        auto program = _shader->Program;
        glUseProgram(program);
        for (int i = 0; i < definition.NumAttributes; i++)
        {
            const auto attrib = &definition.ShaderLayout[i];

            GLint location = glGetAttribLocation(program, attrib->Name);
            glEnableVertexAttribArray(location);

            int size;
            GLenum type = GL_FLOAT;
            bool normalized = false;

            switch (attrib->Type)
            {
                case AttributeType::Float:
                    size = 1;
                    break;
                case AttributeType::Float2:
                    size = 2;
                    break;
                case AttributeType::Float3:
                    size = 3;
                    break;
                case AttributeType::Float4:
                    size = 4;
                    break;
                default:
                    throw std::runtime_error("Invalid attribute type.");
            }

            glVertexAttribPointer(location, size, type, normalized, static_cast<GLsizei>(_stride), reinterpret_cast<void*>(attrib->ByteOffset));
        }

        for (int i = 0; i < definition.NumUniforms; i++)
        {
            const auto uniform = &definition.Uniforms[i];

            switch (uniform->Type)
            {
                case UniformType::ConstantBuffer:
                {
                    const auto index = glGetUniformBlockIndex(program, uniform->Name.c_str());
                    glUniformBlockBinding(program, index, uniform->BindPoint);

                    GLuint uniformBuffer;
                    glGenBuffers(1, &uniformBuffer);
                    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
                    glBufferData(GL_UNIFORM_BUFFER, uniform->BufferSize, nullptr, GL_DYNAMIC_DRAW);
                    glBindBuffer(GL_UNIFORM_BUFFER, 0);

                    _uniformBuffers.emplace(uniform->BindPoint, uniformBuffer);
                    break;
                }
                case UniformType::Texture:
                {
                    const auto location = glGetUniformLocation(program, uniform->Name.c_str());
                    glUniform1ui(location, uniform->BindPoint);
                    break;
                }
                default:
                    throw std::runtime_error("Invalid uniform type.");
            }
        }
    }

    GLRenderable::~GLRenderable()
    {
        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    void GLRenderable::PushUniformData(uint32_t bindPoint, uint32_t dataSize, void* data)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _uniformBuffers[bindPoint]);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, dataSize, data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GLRenderable::PushTexture(uint32_t bindPoint, Texture* texture)
    {
        auto glTexture = dynamic_cast<GLTexture*>(texture);

        glActiveTexture(GL_TEXTURE0 + bindPoint);
        glBindTexture(GL_TEXTURE_2D, glTexture->Texture);
    }

    void GLRenderable::Update(const RenderableUpdateInfo& info)
    {
        glBindVertexArray(0);

        if (info.NumVertices > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, info.NumVertices, info.Vertices);
        }

        if (info.NumIndices > 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(info.NumIndices * sizeof(uint32_t)), info.Indices);
        }
    }

    void GLRenderable::Draw(uint32_t numDraws)
    {
        glBindVertexArray(_vao);
        glUseProgram(_shader->Program);

        for (const auto& buffer : _uniformBuffers)
            glBindBufferBase(GL_UNIFORM_BUFFER, buffer.first, buffer.second);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(numDraws), GL_UNSIGNED_INT, nullptr);
    }
}
