#include "Mesh.h"
#include <string>
#include <iostream>
#include "../Debug.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture>&& textures)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_material(std::move(textures)) {
    m_vao.bind();

    m_vbo.init(m_vertices);
    m_ebo.init(m_indices);

    VAO::linkAttrib(m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);                                    // position
    VAO::linkAttrib(m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float))); // normal
    VAO::linkAttrib(m_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float))); // tex coords
    VAO::linkAttrib(m_vbo, 3, 4, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(8 * sizeof(float))); // tangent

    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();
}

void Mesh::draw(const Shader& shader) const {
    m_vao.bind();

    m_material.apply(shader);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    m_vao.unbind();
}
