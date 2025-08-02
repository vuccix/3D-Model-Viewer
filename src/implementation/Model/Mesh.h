#pragma once

#include <glad/gl.h>
#include <vector>
#include <memory>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../Shader.h"
#include "Texture.h"

using ATexture = std::shared_ptr<Texture>;

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<ATexture> textures);

    void draw(const Shader& shader) const;

private:
    std::vector<Vertex>   m_vertices;
    std::vector<GLuint>   m_indices;
    std::vector<ATexture> m_textures;

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};
