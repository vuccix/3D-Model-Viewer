#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
   ~Shader();

    void use() const;
    void deleteShader() const;
    void reloadShader(const char* vertexPath, const char* fragmentPath);

    GLuint getID() const { return id; }

    template <typename T>
    void setUniform(const char* name, const T& value);

private:
    GLuint id;

    static std::string loadShaderSource(const char* filepath);
    static void compileErrors(GLuint shader, const char* type);
    static GLuint compileShader(const char* vertexPath, const char* fragmentPath);
};

template<typename T>
void Shader::setUniform(const char* name, const T& value) {
    if (!name) throw std::runtime_error("Shader::setUniform: name is null");

    if constexpr (std::is_same_v<T, float>)
        glUniform1f(glGetUniformLocation(id, name), value);

    else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, bool>)
        glUniform1i(glGetUniformLocation(id, name), value);

    else if constexpr (std::is_same_v<T, glm::vec2>)
        glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));

    else if constexpr (std::is_same_v<T, glm::vec3>)
        glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));

    else if constexpr (std::is_same_v<T, glm::vec4>)
        glUniform4fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));

    else if constexpr (std::is_same_v<T, glm::mat3>)
        glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));

    else if constexpr (std::is_same_v<T, glm::mat4>)
        glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));
}
