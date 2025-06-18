#pragma once

#include <glad/gl.h>

class EBO {
public:
    EBO(const GLuint* indices, GLsizei size);
   ~EBO();

    void bind() const;
    void unbind() const;
    void deleteEBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
