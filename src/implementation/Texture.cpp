#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(const char* path, const GLuint slot) : unit(slot) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << "\n";
        return;
    }

    GLenum format;
    switch (nrChannels) {
        case 3:  format = GL_RGB;  break;
        case 4:  format = GL_RGBA; break;
        default: format = GL_RED;  break;
    }

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() { glDeleteTextures(1, &id); }

void Texture::texUnit(const Shader& shader, const char* uniformName, const GLint unit) {
    shader.use();
    glUniform1i(glGetUniformLocation(shader.getID(), uniformName), unit);
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
