#include "EBO.h"

EBO::EBO(const GLuint* indices, const GLsizei size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() { glDeleteBuffers(1, &id); }

void EBO::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

void EBO::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::deleteEBO() const { glDeleteBuffers(1, &id); }
