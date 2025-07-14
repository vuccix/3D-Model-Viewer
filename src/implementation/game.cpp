#include "Game.h"

#include <format>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"
#define IMAGE_PATH  "../src/resources/Bricks_D.jpg"

Game::Game()
        : shader(VERTEX_PATH, FRAG_PATH),
          texture(IMAGE_PATH, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE),
          camera(glm::vec3(0.f, 0.5f, 2.f)) {
    vao.bind();

    vbo.init(vertices, sizeof(vertices));
    ebo.init(indices, sizeof(indices));

    VAO::linkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), nullptr);
    VAO::linkAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    VAO::linkAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    VAO::linkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), reinterpret_cast<void*>(8 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    Texture::texUnit(shader, "albedo", 0);

    const GLint modelLoc = glGetUniformLocation(shader.getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pyramidModel));

    const GLint lightLoc = glGetUniformLocation(shader.getID(), "lightPos");
    if (lightLoc == -1) { exit(EXIT_FAILURE); }
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
}

void Game::render() {
    shader.use();

    camera.updateMatrix(45.f, 0.1f, 100.f);
    camera.sendMatrix(shader, "MVP");

    texture.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
}

void Game::inputs() {
    GLFWwindow* window = glfwGetCurrentContext();

    // close app
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // reload shaders
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        shader.reloadShader(VERTEX_PATH, FRAG_PATH);

        Texture::texUnit(shader, "albedo", 0);

        const GLint modelLoc = glGetUniformLocation(shader.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pyramidModel));

        const GLint lightLoc = glGetUniformLocation(shader.getID(), "lightPos");
        if (lightLoc == -1) { exit(EXIT_FAILURE); }
        glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
    }

    // camera movement
    camera.inputs(window);
}
