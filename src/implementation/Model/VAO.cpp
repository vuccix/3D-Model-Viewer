#include "VAO.h"

VAO::VAO() { glGenVertexArrays(1, &id); }

VAO::~VAO() { glDeleteVertexArrays(1, &id); }

void VAO::linkAttrib(const VBO& vbo, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, const void* offset) {
    vbo.bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() const { glBindVertexArray(id); }

void VAO::unbind() const { glBindVertexArray(0); }

void VAO::deleteVAO() const { glDeleteVertexArrays(1, &id); }
