#include "Shader.h"
#include <glm/glm.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
// #include <filesystem>

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

void Shader::compileErrors(const GLuint shader, const char* type) {
    GLint status;
    char infoLog[1024];

    if (std::strcmp(type, "PROGRAM") == 0) {
        // check program link status
        glGetProgramiv(shader, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "PROGRAM_LINK_ERROR:\n" << infoLog << "\n";
        }
    }
    else {
        // check shader compile status
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << type << "_COMPILE_ERROR:\n" << infoLog << "\n";
        }
    }
}

GLuint Shader::compileShader(const char* vertexPath, const char* fragmentPath) {
    // std::cout << std::filesystem::current_path() << std::endl; // for debugging

    const auto vertex   = loadShaderSource(vertexPath);
    const auto fragment = loadShaderSource(fragmentPath);

    const char* vertSrc = vertex.c_str();
    const char* fragSrc = fragment.c_str();

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, nullptr);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    compileErrors(program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) : id(compileShader(vertexPath, fragmentPath)) {}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::use() const { glUseProgram(id); }

void Shader::deleteShader() const { glDeleteProgram(id); }

void Shader::reloadShader(const char* vertexPath, const char* fragmentPath) {
    const GLuint newID = compileShader(vertexPath, fragmentPath);
    deleteShader();
    id = newID;
}
