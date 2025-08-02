#pragma once

#include <glad/gl.h>
#include "../Shader.h"

struct Image {
    unsigned char* data;
    int width, height, nrChannels;
};

class Texture {
public:
    Texture(const Image& img, const char* texType, GLuint slot);
   ~Texture();

    static void texUnit(const Shader& shader, const char* uniformName, GLint unit);
    void bind() const;
    void unbind() const;

    GLuint getID() const { return id; }
    const char* getType() const { return type; }
    GLuint getUnit() const { return unit; }

private:
    GLuint      id{};
    const char* type;
    GLuint      unit{};
};
