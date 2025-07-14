#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
   ~Shader();

    void use() const;
    void deleteShader() const;
    void reloadShader(const char* vertexPath, const char* fragmentPath);

    GLuint getID() const { return id; }

private:
    GLuint id;

    static std::string loadShaderSource(const char* filepath);
    static void compileErrors(unsigned shader, const char* type);
    static GLuint compileShader(const char* vertexPath, const char* fragmentPath);
};
