#pragma once

#include <glad/gl.h>
#include "../shaders/Shader.h"
#include "Mesh.h"
#include "Camera.h"

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
};
