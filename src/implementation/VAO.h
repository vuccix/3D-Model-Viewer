#pragma once

#include <glad/gl.h>
#include "VBO.h"

class VAO {
public:
    VAO();
   ~VAO();

    void linkVBO(VBO& vbo, GLuint layout);
    void bind() const;
    void unbind() const;
    void deleteVAO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
