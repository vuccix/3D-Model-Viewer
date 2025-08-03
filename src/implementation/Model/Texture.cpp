#include "Texture.h"
#include <iostream>

Texture::Texture(const Image& img, const char* texType, const GLuint slot) : type(texType), unit(slot) {
    if (!img.data) {
        std::cerr << "Failed to load texture\n";
        return;
    }

    GLenum format;
    switch (img.nrChannels) {
        case 3:  format = GL_RGB;  break;
        case 4:  format = GL_RGBA; break;
        default: format = GL_RED;  break;
    }

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    const GLint internalFormat = img.nrChannels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, img.width, img.height, 0, format, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    if (id != 0)
        glDeleteTextures(1, &id);
}

Texture::Texture(Texture&& other) noexcept : id(other.id), type(other.type), unit(other.unit) {
    other.id = 0;  // prevent deletion
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        glDeleteTextures(1, &id); // delete current

        id       = other.id;
        type     = other.type;
        unit     = other.unit;
        other.id = 0;
    }
    return *this;
}

void Texture::texUnit(const Shader& shader, const char* uniformName, const GLint unit) {
    glUniform1i(glGetUniformLocation(shader.getID(), uniformName), unit);
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
