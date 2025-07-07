#pragma once

#include <glad/gl.h>

class VBO {
public:
    VBO() = default;
   ~VBO();

    void init(const GLfloat* vertices, GLsizeiptr size);

    void bind() const;
    void unbind() const;
    void deleteVBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
