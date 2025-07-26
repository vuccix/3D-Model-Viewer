#pragma once

#include <glad/gl.h>
#include "../shaders/Shader.h"
#include "Mesh.h"
#include "Camera.h"

#define ALBEDO_PATH   "../src/resources/Bricks_D.jpg"
#define SPECULAR_PATH "../src/resources/Bricks_S.jpg"

class Game {
public:
    Game();

    void render();
    void inputs();

private:
    Shader m_shader;
    Camera m_camera;
	Mesh   m_mesh;

	std::vector<Vertex>  m_vertices = {
		Vertex{glm::vec3(-1.f, 0.f,  1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(0.f, 0.f)},
		Vertex{glm::vec3(-1.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(0.f, 1.f)},
		Vertex{glm::vec3( 1.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)},
		Vertex{glm::vec3( 1.f, 0.f,  1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(1.f, 0.f)},
	};
	std::vector<GLuint>  m_indices = {
		0, 1, 2,
		0, 2, 3
	};
	std::vector<Texture> m_textures;

    // glm::vec3 cameraPos    = glm::vec3(0.f, 0.5f, 2.f);
    glm::vec3 lightPos     = glm::vec3(0.5f, 0.5f, 0.5f);
};
