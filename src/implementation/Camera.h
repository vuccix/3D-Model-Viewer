#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Camera {
public:
    Camera(const glm::vec3& position);

    void updateMatrix(float FOV_deg, float near, float far);
    void sendMatrix(const Shader& shader, const char* uniform);

    void inputs(GLFWwindow* window);

    glm::vec3 getPosition() const { return m_position; }

private:
    glm::vec3 m_position;
    glm::vec3 m_target = { 0.f, 0.f, -1.f };
    glm::vec3 m_up     = { 0.f, 1.f,  0.f };
    glm::mat4 m_matrix = { 1.f };
    glm::mat4 m_projection{};

    int   m_width{}, m_height{};
    float m_angleH, m_angleV;
    float m_sensitivity = 30.f;
    float m_speed       = 0.00025f;

    bool firstClick = true;

    void update();
};
