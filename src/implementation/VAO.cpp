#include "VAO.h"

VAO::VAO() { glGenVertexArrays(1, &id); }

VAO::~VAO() { glDeleteVertexArrays(1, &id); }

void VAO::linkVBO(VBO& vbo, const GLuint layout) {
    vbo.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() const { glBindVertexArray(id); }

void VAO::unbind() const { glBindVertexArray(0); }

void VAO::deleteVAO() const { glDeleteVertexArrays(1, &id); }
