#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>
#include "implementation/Game.h"

#define WIDTH  1024
#define HEIGHT 768

void glfwErrorCallback(const int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << '\n';
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    const auto game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) game->onResize();
}

int main() {
    // init GLFW
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    // OpenGL 3.3 Core context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Model Viewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // load OpenGL function pointers via GLAD
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    Game game;

    double prevTime  = 0.;
    double currTime  = 0.;
    double deltaTime = 0.;
    unsigned counter = 0;

    // main game loop
    while (!glfwWindowShouldClose(window)) {
        // FPS counter ----------------------------------------------------------------------------
        currTime  = glfwGetTime();
        deltaTime = currTime - prevTime;
        ++counter;
        if (deltaTime >= 1. / 30.) {
            const std::string FPS      = std::format("{}", static_cast<unsigned>((1. / deltaTime) * counter));
            const std::string newTitle = std::format("3D Model Viewer - {} FPS", FPS);
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = currTime;
            counter  = 0;
        }
        // ----------------------------------------------------------------------------------------

        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game.inputs();
        game.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
