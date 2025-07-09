#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../shaders/Shader.h"
#include "Texture.h"
#include "Camera.h"

class Game {
public:
    Game();

    void render() const;
    void inputs();

private:
    VAO vao;
    VBO vbo;
    EBO ebo;

    Shader  shader;
    Texture texture;
    Camera  camera;

    GLfloat vertices[5 * 8] = {
        // Coords               // Colors                 // TexCoords
       -0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f,
       -0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f,
        0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f,
        0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f,
        0.0f, 0.8f,  0.0f, /**/ 0.92f, 0.86f, 0.76f, /**/ 2.5f, 5.0f,
    };
    GLuint indices[6 * 3] = {
        0, 2, 1,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,
    };
};
