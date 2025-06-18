#include "Shader.h"
#include <fstream>
#include <iostream>

std::string Shader::loadShaderSource(const char* filepath) {
    if (std::ifstream in(filepath, std::ios::binary); in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], static_cast<std::streamsize>(contents.size()));
        in.close();
        return contents;
    }

    throw std::runtime_error("Failed to load shader file");
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    const auto vertex   = loadShaderSource(vertexPath);
    const auto fragment = loadShaderSource(fragmentPath);
    
    const char* vertSrc = vertex.c_str();
    const char* fragSrc = fragment.c_str();

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, nullptr);
    glCompileShader(vertexShader);

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
    glCompileShader(fragmentShader);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::use() const { glUseProgram(id); }

void Shader::deleteShader() const { glDeleteProgram(id); }
