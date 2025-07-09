#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "implementation/Game.h"
#include "shaders/Shader.h"

#define WIDTH  576 //1024
#define HEIGHT 576

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", nullptr, nullptr);
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
    glViewport(0, 0, WIDTH, HEIGHT);

    const Game game;

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
