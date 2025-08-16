#pragma once

#include <glad/gl.h>
#include "../Shader.h"

struct Image {
    uint8_t* data;
    int width, height, nrChannels;
};

class Texture {
public:
    Texture(const Image& img, const char* texType, GLuint slot);
   ~Texture();

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    Texture(const Texture&)            = delete;
    Texture& operator=(const Texture&) = delete;

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
