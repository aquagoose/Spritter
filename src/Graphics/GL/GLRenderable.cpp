#include "GLRenderable.h"

namespace Spritter::Graphics::GL
{
    GLRenderable::GLRenderable(const RenderableDefinition& definition)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        const auto usage = definition.Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, definition.NumVertices, definition.Vertices, usage);

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ARRAY_BUFFER, definition.NumIndices, definition.Indices, usage);

        Shader = dynamic_cast<GLShader*>(definition.Shader);
    }

    GLRenderable::~GLRenderable()
    {
        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }
}
