#include "Game.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"
#define MODEL_PATH  "../src/resources/stanford_dragon_pbr.glb" // "../src/resources/monk.glb"

Game::Game() : m_shader(VERTEX_PATH, FRAG_PATH), m_camera(glm::vec3(0.f, 0.5f, 2.f)) {
    m_shader.use();

    m_model.init(MODEL_PATH);

    constexpr glm::vec3 lightPos(0.75f); // (-0.75f, 0.75f, -0.75f);
    m_shader.setUniform("model", glm::mat4(0.01f));
    m_shader.setUniform("lightPos", lightPos);

    glfwSetWindowUserPointer(glfwGetCurrentContext(), this);
    m_camera.updateMatrix(45.f, 0.1f, 100.f);
}

void Game::render() {
    m_shader.use();
    m_camera.sendMatrix(m_shader, "MVP");
    m_model.draw(m_shader);
}

void Game::inputs() {
    GLFWwindow* window = glfwGetCurrentContext();

    // close app
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // camera movement
    m_camera.inputs(window);
}

void Game::onResize() {
    m_camera.updateMatrix(45.f, 0.1f, 100.f);
}
