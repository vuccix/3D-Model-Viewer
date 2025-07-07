#pragma once

#include <glad/gl.h>

class EBO {
public:
    EBO() = default;
   ~EBO();

    void init(const GLuint* indices, GLsizei size);

    void bind() const;
    void unbind() const;
    void deleteEBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
