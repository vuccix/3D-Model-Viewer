#include "Model.h"
#include "../Debug.h"
#include <iostream>

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

void Model::init(const char* path) {
    cgltf_options options = {};
    cgltf_data* data = nullptr;

    // parse file
    cgltf_result result = cgltf_parse_file(&options, path, &data);
    if (result != cgltf_result_success)
        throw std::runtime_error("Failed to load model from file " + std::string(path));

    // load binary buffers
    result = cgltf_load_buffers(&options, data, "model.glb");
    if (result != cgltf_result_success) {
        cgltf_free(data);
        throw std::runtime_error("Failed to load buffers");
    }

    // validate GLTF
    result = cgltf_validate(data);
    if (result != cgltf_result_success) {
        cgltf_free(data);
        throw std::runtime_error("Failed to validate GLTF model");
    }

    // count meshes
    size_t meshCnt = 0;
    for (cgltf_size i = 0; i < data->meshes_count; ++i) {
        const cgltf_mesh& gltf_mesh = data->meshes[i];

        for (cgltf_size j = 0; j < gltf_mesh.primitives_count; ++j)
            ++meshCnt;
    }

    m_meshes.reserve(meshCnt);

    // create meshes
    for (cgltf_size i = 0; i < data->meshes_count; ++i) {
        const cgltf_mesh& gltf_mesh = data->meshes[i];

        for (cgltf_size j = 0; j < gltf_mesh.primitives_count; ++j) {
            const cgltf_primitive& prim = gltf_mesh.primitives[j];

            std::vector<Vertex> vertices;
            std::vector<GLuint> indices;

            // parse attributes
            cgltf_accessor* pos_accessor  = nullptr;
            cgltf_accessor* norm_accessor = nullptr;
            cgltf_accessor* tex_accessor  = nullptr;

            for (cgltf_size k = 0; k < prim.attributes_count; ++k) {
                const cgltf_attribute& attr = prim.attributes[k];
                if (strcmp(attr.name, "POSITION")   == 0) pos_accessor  = attr.data;
                if (strcmp(attr.name, "NORMAL")     == 0) norm_accessor = attr.data;
                if (strcmp(attr.name, "TEXCOORD_0") == 0) tex_accessor  = attr.data;
            }

            size_t vertexCount = pos_accessor ? pos_accessor->count : 0;
            vertices.resize(vertexCount);

            for (size_t v = 0; v < vertexCount; ++v) {
                Vertex vert = {};

                float pos[3];
                cgltf_accessor_read_float(pos_accessor, v, pos, 3);
                vert.position = glm::vec3(pos[0], pos[1], pos[2]);

                if (norm_accessor) {
                    float norm[3];
                    cgltf_accessor_read_float(norm_accessor, v, norm, 3);
                    vert.normal = glm::vec3(norm[0], norm[1], norm[2]);
                }

                if (tex_accessor) {
                    float uv[2];
                    cgltf_accessor_read_float(tex_accessor, v, uv, 2);
                    vert.texCoords = glm::vec2(uv[0], uv[1]);
                }

                vert.color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

                vertices[v] = vert;
            }

            // parse indices
            if (prim.indices) {
                size_t indexCount = prim.indices->count;
                indices.reserve(indexCount);

                for (size_t idx = 0; idx < indexCount; ++idx) {
                    auto index = static_cast<uint32_t>(cgltf_accessor_read_index(prim.indices, idx));
                    indices.push_back(index);
                }
            }

            // create mesh
            m_meshes.emplace_back(vertices, indices, std::vector<Texture>());
        }
    }

    cgltf_free(data);
}

void Model::draw(const Shader& shader, const Camera& camera) const {
    for (const Mesh& mesh : m_meshes)
        mesh.draw(shader, camera);
}
