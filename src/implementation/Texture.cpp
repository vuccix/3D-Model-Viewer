#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(const char* path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) : type(texType) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << "\n";
        return;
    }

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(texType, id);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
    glGenerateMipmap(texType);

    stbi_image_free(data);
    glBindTexture(texType, 0);
}

Texture::~Texture() { glDeleteTextures(1, &id); }

void Texture::texUnit(const Shader& shader, const char* uniformName, const GLint unit) {
    shader.use();
    glUniform1i(glGetUniformLocation(shader.getID(), uniformName), unit);
}

void Texture::bind() const { glBindTexture(type, id); }

void Texture::unbind() const { glBindTexture(type, 0); }
