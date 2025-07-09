#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shaders/Shader.h"

class Camera {
public:
    Camera(int width, int height, const glm::vec3& position);

    void matrix(float FOVdeg, float near, float far, const Shader& shader, const char* uniform) const;
    void inputs(GLFWwindow* window);

private:
    glm::vec3 position;
    glm::vec3 orientation = {0.f, 0.f, -1.f};
    glm::vec3 up          = {0.f, 1.f,  0.f};

    int   width, height;
    float speed       = 0.0001f;
    float sensitivity = 30.f;
    float angleH{}, angleV{};

    bool firstClick = true;

    void update();
    void init();
};
