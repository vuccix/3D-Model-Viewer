#pragma once

#include <glad/gl.h>
#include "../shaders/Shader.h"

class Texture {
public:
    Texture(const char* path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
   ~Texture();

    static void texUnit(const Shader& shader, const char* uniformName, GLint unit);
    void bind() const;
    void unbind() const;

    GLuint getID() const { return id; }

private:
    GLenum type{};
    GLuint id{};
};
