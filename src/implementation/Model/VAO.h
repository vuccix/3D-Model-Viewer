#pragma once

#include <glad/gl.h>
#include "VBO.h"

class VAO {
public:
    VAO();
   ~VAO();

    static void linkAttrib(const VBO& vbo, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, const void* offset);
    void bind() const;
    void unbind() const;
    void deleteVAO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
