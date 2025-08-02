#pragma once

#include <vector>
#include "../Shader.h"
#include "Mesh.h"

class Model {
public:
    Model() = default;

    void init(const char* path);
    void draw(const Shader& shader) const;

private:
    std::vector<Mesh> m_meshes;
};
