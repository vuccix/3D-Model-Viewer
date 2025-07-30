#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texCoords;
};

class VBO {
public:
    VBO() = default;
   ~VBO();

    void init(const std::vector<Vertex>& vertices);
    void bind() const;
    void unbind() const;
    void deleteVBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
