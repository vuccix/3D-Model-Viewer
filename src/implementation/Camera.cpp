#include "Camera.h"

Camera::Camera(int width, int height, const glm::vec3& position)
        : position(position), width(width), height(height) {
    init();
}

void Camera::init() {
    glm::vec3 hTarget(orientation.x, 0.0f, orientation.z);
    hTarget = glm::normalize(hTarget);

    const float angle = glm::degrees(glm::asin(abs(hTarget.z)));

    if (hTarget.z >= 0.0f) {
        if (hTarget.x >= 0.0f)
            angleH = 360.f - angle;
        else
            angleH = 180.f + angle;
    }
    else {
        if (hTarget.x >= 0.0f)
            angleH = angle;
        else
            angleH = 180.f - angle;
    }

    angleV = -glm::degrees(glm::asin(orientation.y));
}

void Camera::matrix(float FOVdeg, float near, float far, const Shader& shader, const char* uniform) const {
    const float aspect = static_cast<float>(width) / static_cast<float>(height);

    const glm::mat4 view       = glm::lookAt(position, position + orientation, up);
    const glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), aspect, near, far);

    const GLint loc = glGetUniformLocation(shader.getID(), uniform);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow* window) {
    // WASD movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * orientation;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed * orientation;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= speed * glm::normalize(glm::cross(orientation, up));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += speed * glm::normalize(glm::cross(orientation, up));

    // Up and Down movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += speed * up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= speed * up;

    // camera rotation
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick) {
            firstClick = false;
            glfwSetCursorPos(window, width / 2., height / 2.);
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        const double centerX = width  / 2.;
        const double centerY = height / 2.;

        const double DeltaX = mouseX - centerX;
        const double DeltaY = mouseY - centerY;

        angleH -= static_cast<float>(DeltaX) / sensitivity;
        angleV += static_cast<float>(DeltaY) / sensitivity;

        if (angleV > 89.0f)
            angleV = 89.0f;
        if (angleV < -89.0f)
            angleV = -89.0f;

        update();
        glfwSetCursorPos(window, width / 2., height / 2.);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

void Camera::update() {
    constexpr glm::vec3 yAxis(0.f, 1.f, 0.f);

    const glm::quat quaternion = glm::angleAxis(glm::radians(angleH), yAxis);
    glm::vec3 view = glm::normalize(quaternion * glm::vec3(1.f, 0.f, 0.f));

    const glm::vec3 U = glm::normalize(cross(yAxis, view));
    const glm::quat quaternion1 = glm::angleAxis(glm::radians(angleV), U);
    view = quaternion1 * view;

    orientation = glm::normalize(view);
    up = glm::normalize(cross(orientation, U));
}
