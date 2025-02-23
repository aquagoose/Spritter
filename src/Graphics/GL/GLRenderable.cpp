#include "GLRenderable.h"

#include <stdexcept>

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
            auto attrib = &definition.ShaderLayout[i];

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
    }

    GLRenderable::~GLRenderable()
    {
        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    void GLRenderable::Update(const RenderableUpdateInfo& info)
    {
        glBindVertexArray(_vao);

        if (info.NumVertices > 0)
            glBufferSubData(GL_ARRAY_BUFFER, 0, info.NumVertices, info.Vertices);

        if (info.NumIndices > 0)
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(info.NumIndices * sizeof(uint32_t)), info.Indices);
    }

    void GLRenderable::Draw(uint32_t numDraws)
    {
        glBindVertexArray(_vao);
        glUseProgram(_shader->Program);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(numDraws), GL_UNSIGNED_INT, nullptr);
    }
}
