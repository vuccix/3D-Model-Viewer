#include "Mesh.h"
#include <string>
#include <iostream>
#include "../Debug.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture>&& textures)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_textures(std::move(textures)) {
    m_vao.bind();

    m_vbo.init(m_vertices);
    m_ebo.init(m_indices);

    VAO::linkAttrib(m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);                                    // position
    VAO::linkAttrib(m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float))); // normal
    VAO::linkAttrib(m_vbo, 2, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float))); // color
    VAO::linkAttrib(m_vbo, 3, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(9 * sizeof(float))); // tex coords

    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();
}

void Mesh::draw(const Shader& shader) const {
    shader.use();
    m_vao.bind();

    size_t numDiff = 0;
    size_t numSpec = 0;
    size_t numNorm = 0;

    for (size_t i = 0; i < m_textures.size(); ++i) {
        std::string num;
        std::string type = m_textures[i].getType();

        if (type == "diffuse")
            num = std::to_string(numDiff++);
        else if (type == "specular")
            num = std::to_string(numSpec++);
        else if (type == "normal")
            num = std::to_string(numNorm++);

        // Texture::texUnit(shader, (type + num).c_str(), static_cast<GLint>(i));
        // m_textures[i]->bind();

        glUniform1i(glGetUniformLocation(shader.getID(), (type + num).c_str()), static_cast<GLint>(i));
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].getID());

        checkGLError("bind texture");
    }

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    m_vao.unbind();

    glActiveTexture(GL_TEXTURE0);
}
