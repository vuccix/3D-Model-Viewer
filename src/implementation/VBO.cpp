#include "VBO.h"

VBO::~VBO() { glDeleteBuffers(1, &id); }

void VBO::init(const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }

void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::deleteVBO() const { glDeleteBuffers(1, &id); }
