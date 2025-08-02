#include "Game.h"

#include <iostream>
#include <bits/ostream.tcc>
#include <glm/glm.hpp>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"
#define MODEL_PATH  "../src/resources/monk.glb"

Game::Game() : m_shader(VERTEX_PATH, FRAG_PATH), m_camera(glm::vec3(0.f, 0.5f, 2.f)) {
    m_shader.use();

    m_model.init(MODEL_PATH);

    const GLint modelLoc = glGetUniformLocation(m_shader.getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(0.5f)));

    constexpr glm::vec3 lightPos(0.75f);
    const GLint lightLoc = glGetUniformLocation(m_shader.getID(), "lightPos");
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
}

void Game::render() {
    m_shader.use();

    m_camera.updateMatrix(45.f, 0.1f, 100.f);
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
