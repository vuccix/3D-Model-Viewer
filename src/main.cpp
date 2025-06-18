#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "implementation/Game.h"
#include "shaders/Shader.h"
#include "implementation/VBO.h"
#include "implementation/VAO.h"
#include "implementation/EBO.h"

// error callback
void glfwErrorCallback(const int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << '\n';
}

int main() {
    // init GLFW
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // OpenGL 3.3 Core context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(1024, 576, "OpenGL Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    // load OpenGL function pointers via GLAD
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return 1;
    }

    // set viewport
    glViewport(0, 0, 1024, 576);

    const Shader shader("../src/shaders/default.vert", "../src/shaders/default.frag");

    // --------------------------------------------------------------------------------------------
    constexpr GLfloat vertices[] = {
        -.5f,       -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
         .5f,       -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
        0.f,         .5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
        -.5f / 2.f,  .5f * static_cast<float>(sqrt(3)) / 6.f, 0.f,
         .5f / 2.f,  .5f * static_cast<float>(sqrt(3)) / 6.f, 0.f,
        0.f,        -.5f * static_cast<float>(sqrt(3)) / 3.f, 0.f,
    };
    constexpr GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1,
    };

    VAO vao;
    vao.bind();

    VBO vbo(vertices, sizeof(vertices));
    const EBO ebo(indices, sizeof(indices));

    vao.linkVBO(vbo, 0);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
    // --------------------------------------------------------------------------------------------

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ----------------------------------------------------------------------------------------
        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
        // ----------------------------------------------------------------------------------------

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
