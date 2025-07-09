#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"
#define IMAGE_PATH  "../src/resources/Bricks_D.jpg"
#define WIDTH  576 //1024
#define HEIGHT 576

Game::Game()
        : shader(VERTEX_PATH, FRAG_PATH),
          texture(IMAGE_PATH, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE),
          camera(WIDTH, HEIGHT, glm::vec3(0.f, 0.f, 2.f)) {
    vao.bind();

    vbo.init(vertices, sizeof(vertices));
    ebo.init(indices, sizeof(indices));

    VAO::linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
    VAO::linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    VAO::linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    Texture::texUnit(shader, "tex0", 0);
}

void Game::render() const {
    shader.use();

    camera.matrix(45.f, 0.1f, 100.f, shader, "MVP");

    texture.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
}

void Game::inputs() {
    GLFWwindow* window = glfwGetCurrentContext();

    // close app
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // camera movement
    camera.inputs(window);
}
