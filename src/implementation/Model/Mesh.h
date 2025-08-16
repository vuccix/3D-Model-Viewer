#pragma once

#include <glad/gl.h>
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../Shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture>&& textures);

    void draw(const Shader& shader) const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    Material            m_material;

    size_t              m_material_ID{};

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};
