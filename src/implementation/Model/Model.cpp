#include "Model.h"
#include "../Debug.h"
#include <stb/stb_image.h>
#include <iostream>

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

Image loadTexture(const cgltf_image* image) {
    if (!image) throw std::runtime_error("image is null");

    if (const cgltf_buffer_view* view = image->buffer_view; view) {
        const uint8_t* imageData = static_cast<const uint8_t*>(view->buffer->data) + view->offset;
        int w, h, channels;

        const int viewSize = static_cast<int>(view->size);
        unsigned char* decoded = stbi_load_from_memory(imageData, viewSize, &w, &h, &channels, 0);
        if (!decoded)
            throw std::runtime_error("Failed to decode embedded image");

        return { decoded, w, h, channels };
    }

    throw std::runtime_error("Failed to load texture");
}

void Model::init(const char* path) {
    cgltf_options options = {};
    cgltf_data* data = nullptr;

    // parse file
    cgltf_result result = cgltf_parse_file(&options, path, &data);
    if (result != cgltf_result_success)
        throw std::runtime_error("Failed to load model from file " + std::string(path));

    // load binary buffers
    result = cgltf_load_buffers(&options, data, path);
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
        for (cgltf_size j = 0; j < data->meshes[i].primitives_count; ++j)
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
            cgltf_accessor* tang_accessor = nullptr;

            for (cgltf_size k = 0; k < prim.attributes_count; ++k) {
                const cgltf_attribute& attr = prim.attributes[k];
                if (strcmp(attr.name, "POSITION")   == 0) pos_accessor  = attr.data;
                if (strcmp(attr.name, "NORMAL")     == 0) norm_accessor = attr.data;
                if (strcmp(attr.name, "TEXCOORD_0") == 0) tex_accessor  = attr.data;
                if (strcmp(attr.name, "TANGENT")    == 0) tang_accessor = attr.data;
            }

            // parse vertices
            size_t vertexCount = pos_accessor ? pos_accessor->count : 0;
            vertices.resize(vertexCount);

            for (size_t v = 0; v < vertexCount; ++v) {
                Vertex vert = {};

                float pos[3]{};
                cgltf_accessor_read_float(pos_accessor, v, pos, 3);
                vert.position = glm::vec3(pos[0], pos[1], pos[2]);

                if (norm_accessor) {
                    float norm[3]{};
                    cgltf_accessor_read_float(norm_accessor, v, norm, 3);
                    vert.normal = glm::vec3(norm[0], norm[1], norm[2]);
                }

                if (tex_accessor) {
                    float uv[2]{};
                    cgltf_accessor_read_float(tex_accessor, v, uv, 2);
                    vert.texCoords = glm::vec2(uv[0], uv[1]);
                }

                if (tang_accessor) {
                    float tang[4]{};
                    cgltf_accessor_read_float(tang_accessor, v, tang, 4);
                    vert.tangent = glm::vec4(tang[0], tang[1], tang[2], tang[3]);
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

            // parse textures
            std::vector<Texture> textures;
            textures.reserve(3); // Diffuse, Roughness-Metallic, Normal

            if (prim.material) {
                if (const cgltf_material* mat = prim.material; mat->has_pbr_metallic_roughness) {
                    // diffuse texture
                    const cgltf_texture* diffuseTex = mat->pbr_metallic_roughness.base_color_texture.texture;
                    if (diffuseTex && diffuseTex->image) {
                        Image tex = loadTexture(diffuseTex->image);
                        textures.emplace_back(tex, "diffuse", textures.size());
                        stbi_image_free(tex.data);
                    }

                    // metallic-roughness map (specular for now)
                    const cgltf_texture* mrTex = mat->pbr_metallic_roughness.metallic_roughness_texture.texture;
                    if (mrTex && mrTex->image) {
                        Image tex = loadTexture(mrTex->image);
                        textures.emplace_back(tex, "specular", textures.size());
                        stbi_image_free(tex.data);
                    }

                    // normal map
                    const cgltf_texture* normalTex = mat->normal_texture.texture;
                    if (normalTex && normalTex->image) {
                        Image tex = loadTexture(normalTex->image);
                        textures.emplace_back(tex, "normal", textures.size());
                        stbi_image_free(tex.data);
                    }
                }
            }

            // create mesh
            m_meshes.emplace_back(vertices, indices, std::move(textures));
        }
    }

    cgltf_free(data);
}

void Model::draw(const Shader& shader) const {
    for (const Mesh& mesh : m_meshes) {
        mesh.draw(shader);
        checkGLError("mesh.draw");
    }
}
