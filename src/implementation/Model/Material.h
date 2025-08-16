#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../Shader.h"
#include "Texture.h"

class Material {
public:
    Material(std::vector<Texture>&& textures);

    void apply(const Shader& shader) const;

private:
    std::vector<Texture> m_textures;

    glm::vec3 m_color     = glm::vec3(1.0f);
    float     m_specular  = 0.5f;
    float     m_roughness = 0.5f;
    float     m_metallic  = 0.f;
};
