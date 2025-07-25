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
    Texture texture, specular;
    Camera  camera;

    GLfloat vertices[4 * 11] = {
    	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    	1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    	1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
    };
    GLuint indices[2 * 3] = {
    	0, 1, 2,
		0, 2, 3
    };

    glm::vec3 cameraPos    = glm::vec3(0.f, 0.5f, 2.f);
    glm::vec3 lightPos     = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 pyramidPos   = glm::vec3(0.f);
	glm::mat4 pyramidModel = glm::translate(glm::mat4(1.0f), pyramidPos);
};
