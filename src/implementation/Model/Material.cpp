#include "Material.h"
#include "../Debug.h"

Material::Material(std::vector<Texture>&& textures) : m_textures(std::move(textures)) {

}

void Material::apply(const Shader& shader) const {
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

        Texture::texUnit(shader, (type + num).c_str(), static_cast<GLint>(i));
        m_textures[i].bind();

        // glUniform1i(glGetUniformLocation(shader.getID(), (type + num).c_str()), static_cast<GLint>(i));
        // glActiveTexture(GL_TEXTURE0 + i);
        // glBindTexture(GL_TEXTURE_2D, m_textures[i].getID());

        checkGLError("bind texture");
    }
}
