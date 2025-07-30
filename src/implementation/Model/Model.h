#pragma once

#include <vector>
#include "../Shader.h"
#include "../Camera.h"
#include "Mesh.h"

class Model {
public:
    Model() = default;

    void init(const char* path);
    void draw(const Shader& shader, const Camera& camera) const;

private:
    std::vector<Mesh> m_meshes;
};
