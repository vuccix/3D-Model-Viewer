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

    void render();
    void inputs();

private:
    VAO vao;
    VBO vbo;
    EBO ebo;

    Shader  shader;
    Texture texture;
    Camera  camera;

    GLfloat vertices[16 * 11] = {
        // Coords               // Colors                 // TexCoords     // Normals
       -0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f, /**/ 0.0f, -1.0f, 0.0f, // Bottom side
	   -0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 5.0f, /**/ 0.0f, -1.0f, 0.0f, // Bottom side
	    0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 5.0f, /**/ 0.0f, -1.0f, 0.0f, // Bottom side
	    0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f, /**/ 0.0f, -1.0f, 0.0f, // Bottom side

	   -0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f, /**/ -0.8f, 0.5f, 0.0f, // Left Side
	   -0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f, /**/ -0.8f, 0.5f, 0.0f, // Left Side
	    0.0f, 0.8f,  0.0f, /**/ 0.92f, 0.86f, 0.76f, /**/ 2.5f, 5.0f, /**/ -0.8f, 0.5f, 0.0f, // Left Side

	   -0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f, /**/ 0.0f, 0.5f, -0.8f, // Non-facing side
	    0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f, /**/ 0.0f, 0.5f, -0.8f, // Non-facing side
	    0.0f, 0.8f,  0.0f, /**/ 0.92f, 0.86f, 0.76f, /**/ 2.5f, 5.0f, /**/ 0.0f, 0.5f, -0.8f, // Non-facing side

	    0.5f, 0.0f, -0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f, /**/ 0.8f, 0.5f, 0.0f, // Right side
	    0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f, /**/ 0.8f, 0.5f, 0.0f, // Right side
	    0.0f, 0.8f,  0.0f, /**/ 0.92f, 0.86f, 0.76f, /**/ 2.5f, 5.0f, /**/ 0.8f, 0.5f, 0.0f, // Right side

	    0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 5.0f, 0.0f, /**/ 0.0f, 0.5f, 0.8f, // Facing side
	   -0.5f, 0.0f,  0.5f, /**/ 0.83f, 0.70f, 0.44f, /**/ 0.0f, 0.0f, /**/ 0.0f, 0.5f, 0.8f, // Facing side
	    0.0f, 0.8f,  0.0f, /**/ 0.92f, 0.86f, 0.76f, /**/ 2.5f, 5.0f, /**/ 0.0f, 0.5f, 0.8f  // Facing side
    };
    GLuint indices[6 * 3] = {
    	 0,  1,  2, // bottom side
		 0,  2,  3, // bottom side
		 4,  6,  5, // left side
		 7,  9,  8, // non-facing side
		10, 12, 11, // right side
		13, 15, 14  // facing side
    };

    glm::vec3 cameraPos    = glm::vec3(0.f, 0.5f, 2.f);
    glm::vec3 lightPos     = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 pyramidPos   = glm::vec3(0.f);
	glm::mat4 pyramidModel = glm::translate(glm::mat4(1.0f), pyramidPos);
};
