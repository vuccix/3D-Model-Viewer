#pragma once

#include <glad/gl.h>
#include "../shaders/Shader.h"

class Texture {
public:
    Texture(const char* path, const char* texType, GLuint slot);
   ~Texture();

    static void texUnit(const Shader& shader, const char* uniformName, GLint unit);
    void bind() const;
    void unbind() const;

    GLuint getID() const { return id; }
    const char* getType() const { return type; }

private:
    GLuint      id{};
    const char* type;
    GLuint      unit{};
};
