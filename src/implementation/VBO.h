#pragma once

#include <glad/gl.h>

class VBO {
public:
    VBO(const GLfloat* vertices, GLsizeiptr size);
   ~VBO();

    void bind() const;
    void unbind() const;
    void deleteVBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
