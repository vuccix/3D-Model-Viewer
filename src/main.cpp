#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "implementation/game.h"

// error callback
void glfwErrorCallback(const int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << '\n';
}

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.xyz, 1.);\n"
"}\0";
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(.8, .3, .02, 1.);\n"
"}\0";

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

    // --------------------------------------------------------------------------------------------

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(program);

    constexpr GLfloat vertices[] = {
        -.5f, -.5f, 0.f,
        .5f, -.5f, 0.f,
        0.f, .5f, 0.f,
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // --------------------------------------------------------------------------------------------

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --------------------------------------------------------------------------------------------

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);

    // --------------------------------------------------------------------------------------------

    // clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
