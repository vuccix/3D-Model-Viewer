#include "Mesh.h"
#include <string>

void Mesh::init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures) {
    m_vertices = vertices;
    m_indices  = indices;
    m_textures = textures;

    m_vao.bind();

    m_vbo.init(m_vertices);
    m_ebo.init(m_indices);

    VAO::linkAttrib(m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
    VAO::linkAttrib(m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
    VAO::linkAttrib(m_vbo, 2, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float)));
    VAO::linkAttrib(m_vbo, 3, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(9 * sizeof(float)));

    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();
}

void Mesh::draw(const Shader& shader, const Camera& camera) const {
    shader.use();
    m_vao.bind();

    size_t numDiff = 0;
    size_t numSpec = 0;

    for (size_t i = 0; i < m_textures.size(); ++i) {
        std::string num;
        std::string type = m_textures[i].getType();

        if (type == "diffuse")
            num = std::to_string(numDiff++);
        else if (type == "specular")
            num = std::to_string(numSpec++);

        Texture::texUnit(shader, (type + num).c_str(), static_cast<GLint>(i));
        m_textures[i].bind();
    }

    const GLint loc = glGetUniformLocation(shader.getID(), "camPos");
    glUniform3fv(loc, 1, glm::value_ptr(camera.getPosition()));

    camera.sendMatrix(shader, "MVP");

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
