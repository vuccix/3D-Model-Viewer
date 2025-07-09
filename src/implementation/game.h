#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../shaders/Shader.h"
#include "Texture.h"

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

    Shader  shader;
    Texture texture;

    GLfloat vertices[4 * 8] = {
        // Coords              // Colors
       -0.5f, -0.5f, 0.f, /**/ 1.f, 0.f,  0.0f, /**/ 0.f, 0.f,
       -0.5f,  0.5f, 0.f, /**/ 0.f, 1.f,  0.0f, /**/ 0.f, 1.f,
        0.5f,  0.5f, 0.f, /**/ 0.f, 0.f,  1.0f, /**/ 1.f, 1.f,
        0.5f, -0.5f, 0.f, /**/ 1.f, 1.0f, 1.0f, /**/ 1.f, 0.f,
    };
    GLuint indices[6] = {
        0, 2, 1,
        0, 3, 2
    };
};
