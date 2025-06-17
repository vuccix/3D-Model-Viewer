#pragma once

#include <GLFW/glfw3.h>
#include <memory>

class Game {
public:
    Game();

    void render();
    void keyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCB(GLFWwindow* window, int button, int action, int mods);

private:
    void compileShaders();
};
