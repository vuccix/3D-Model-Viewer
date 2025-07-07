#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <cmath>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../shaders/Shader.h"

class Game {
public:
    Game();

    void render() const;
    void keyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCB(GLFWwindow* window, int button, int action, int mods);

private:
    VAO vao;
    VBO vbo;
    EBO ebo;

    Shader shader;

    GLfloat vertices[18] = {
        -.5f,       -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
         .5f,       -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
        0.f,         .5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
        -.5f / 2.f,  .5f * static_cast<float>(sqrt(3)) / 6.f, 0.f,
         .5f / 2.f,  .5f * static_cast<float>(sqrt(3)) / 6.f, 0.f,
        0.f,        -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
    };
    GLuint indices[9] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1,
    };
};
