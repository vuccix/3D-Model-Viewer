#include "EBO.h"

EBO::~EBO() { glDeleteBuffers(1, &id); }

void EBO::init(const std::vector<GLuint>& indices) {
    const auto size = static_cast<GLsizei>(indices.size() * sizeof(GLuint));

    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
}

void EBO::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

void EBO::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::deleteEBO() const { glDeleteBuffers(1, &id); }
