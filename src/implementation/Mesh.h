#pragma once

#include <glad/gl.h>
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

class Mesh {
public:
    Mesh() = default;

    // todo move semantics
    void init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures);
    void draw(const Shader& shader, const Camera& camera) const;

private:
    std::vector<Vertex>  m_vertices;
    std::vector<GLuint>  m_indices;
    std::vector<Texture> m_textures;

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};
