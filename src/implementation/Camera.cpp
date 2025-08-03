#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3& position) : m_position(position) {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetWindowSize(window, &m_width, &m_height);

    glm::vec3 hTarget(m_target.x, 0.f, m_target.z);
    hTarget = glm::normalize(hTarget);

    const float angle = glm::degrees(glm::asin(abs(hTarget.z)));

    if (hTarget.z >= 0.f) {
        if (hTarget.x >= 0.f)
            m_angleH = 360.f - angle;
        else
            m_angleH = 180.f + angle;
    }
    else {
        if (hTarget.x >= 0.f)
            m_angleH = angle;
        else
            m_angleH = 180.f - angle;
    }

    m_angleV = -glm::degrees(glm::asin(m_target.y));
}

void Camera::updateMatrix(const float FOV_deg, const float near, const float far) {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwGetWindowSize(window, &m_width, &m_height);

    const float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
    m_projection = glm::perspective(glm::radians(FOV_deg), aspect, near, far);
}

void Camera::sendMatrix(const Shader& shader, const char* uniform) {
    // send PV matrix
    const GLint loc = glGetUniformLocation(shader.getID(), uniform);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m_matrix));

    // send camera position
    const GLint posLoc = glGetUniformLocation(shader.getID(), "camPos");
    glUniform3fv(posLoc, 1, glm::value_ptr(m_position));

    const glm::mat4 view = glm::lookAt(m_position, m_position + m_target, m_up);
    m_matrix = m_projection * view;
}

void Camera::inputs(GLFWwindow* window) {
    // WASD movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += m_speed * m_target;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= m_speed * m_target;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= m_speed * glm::normalize(glm::cross(m_target, m_up));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += m_speed * glm::normalize(glm::cross(m_target, m_up));

    // Up and Down movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += m_speed * m_up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_position -= m_speed * m_up;

    // camera rotation
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick) {
            firstClick = false;
            glfwSetCursorPos(window, m_width / 2., m_height / 2.);
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        const double centerX = m_width  / 2.;
        const double centerY = m_height / 2.;

        const double DeltaX = mouseX - centerX;
        const double DeltaY = mouseY - centerY;

        m_angleH -= static_cast<float>(DeltaX) / m_sensitivity;
        m_angleV += static_cast<float>(DeltaY) / m_sensitivity;

        if (m_angleV >  89.f) m_angleV =  89.f;
        if (m_angleV < -89.f) m_angleV = -89.f;

        update();
        glfwSetCursorPos(window, m_width / 2., m_height / 2.);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

void Camera::update() {
    constexpr glm::vec3 yAxis(0.f, 1.f, 0.f);

    const glm::quat quaternion = glm::angleAxis(glm::radians(m_angleH), yAxis);
    glm::vec3 view = glm::normalize(quaternion * glm::vec3(1.f, 0.f, 0.f));

    const glm::vec3 U = glm::normalize(cross(yAxis, view));
    const glm::quat quaternion1 = glm::angleAxis(glm::radians(m_angleV), U);
    view = quaternion1 * view;

    m_target = glm::normalize(view);
    m_up = glm::normalize(cross(m_target, U));
}
