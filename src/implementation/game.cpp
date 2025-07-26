#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <format>
#include <iostream>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"

#define ALBEDO_PATH   "../src/resources/Bricks_D.jpg"
#define SPECULAR_PATH "../src/resources/Bricks_S.jpg"

Game::Game() : m_shader(VERTEX_PATH, FRAG_PATH), m_camera(glm::vec3(0.f, 0.5f, 2.f)) {
    m_shader.use();

    // hack solution
    m_textures.reserve(2);
    m_textures.emplace_back(ALBEDO_PATH, "diffuse", 0);
    m_textures.emplace_back(SPECULAR_PATH, "specular", 1);

    m_mesh.init(m_vertices, m_indices, m_textures);

    const GLint modelLoc = glGetUniformLocation(m_shader.getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

    constexpr glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
    const GLint lightLoc = glGetUniformLocation(m_shader.getID(), "lightPos");
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
}

void Game::render() {
    m_shader.use();

    m_camera.updateMatrix(45.f, 0.1f, 100.f);
    m_camera.sendMatrix(m_shader, "MVP");

    m_mesh.draw(m_shader, m_camera);
}

void Game::inputs() {
    GLFWwindow* window = glfwGetCurrentContext();

    // close app
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // reload shaders
    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        m_shader.reloadShader(VERTEX_PATH, FRAG_PATH);

        Texture::texUnit(m_shader, "albedo", 0);

        const GLint modelLoc = glGetUniformLocation(m_shader.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pyramidModel));

        const GLint lightLoc = glGetUniformLocation(m_shader.getID(), "lightPos");
        if (lightLoc == -1) { exit(EXIT_FAILURE); }
        glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
    }*/

    // camera movement
    m_camera.inputs(window);
}
