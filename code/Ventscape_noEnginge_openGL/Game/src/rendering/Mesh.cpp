#include "Mesh.h"
#include "../Game.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "tiny_gltf.h"


#define OFFSET(index) (void*)(index)

namespace Ventgame {

    template<typename T>
    GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
        unsigned int l_buffer = 0;
        glGenBuffers(1, &l_buffer);
        glBindBuffer(bufferType, l_buffer);
        glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);

        return l_buffer;
    }

    tinygltf::Model loadGltf(const std::filesystem::path &gltfAssetPath) {
        tinygltf::TinyGLTF l_loader;
        tinygltf::Model l_model;
        std::string l_err;
        std::string l_warn;

        bool l_res;
        if (gltfAssetPath.extension().string() == ".glb") {
            l_res = l_loader.LoadBinaryFromFile(&l_model, &l_err, &l_warn, gltfAssetPath.string());
        } else {
            l_res = l_loader.LoadASCIIFromFile(&l_model, &l_err, &l_warn, gltfAssetPath.string());
        }

        if (!l_warn.empty()) {
            std::cerr << "[tinygltf] warning: " << l_warn << std::endl;
        }

        if (!l_err.empty()) {
            std::cerr << "[tinygltf] error: " << l_err << std::endl;
        }

        if (!l_res) {
            throw std::runtime_error("[tinygltf] failed to load glTF: " + gltfAssetPath.string());
        }

        return l_model;
    }


    Mesh::Mesh(const std::filesystem::path &gltfAssetPath, int meshIndex) {
        auto l_model = loadGltf(gltfAssetPath);

        if (l_model.meshes.size() <= meshIndex) {
            throw std::runtime_error("[mesh] model does not contain requested mesh: " + gltfAssetPath.string());
        }

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        std::map<int, unsigned int> l_vbos;
        for (size_t l_i = 0; l_i < l_model.bufferViews.size(); ++l_i) {
            const auto &l_bufferView = l_model.bufferViews[l_i];
            const auto &l_buffer = l_model.buffers[l_bufferView.buffer];
            if (l_bufferView.target == 0) {
                std::cerr << "[mesh] bufferView.target is zero, drawArrays not supported: " << gltfAssetPath.string()
                          << std::endl;
                continue;
            }

            GLuint l_vbo;
            glGenBuffers(1, &l_vbo);
            l_vbos[l_i] = l_vbo;
            glBindBuffer(l_bufferView.target, l_vbo);
            glBufferData(l_bufferView.target, l_bufferView.byteLength, &l_buffer.data.at(0) + l_bufferView.byteOffset,
                         GL_STATIC_DRAW);
        }

        const auto &l_mesh = l_model.meshes[meshIndex];
        for (const auto &l_primitive: l_mesh.primitives) {
            const auto &l_indexAccessor = l_model.accessors[l_primitive.indices];
            for (const auto &[l_name, l_value]: l_primitive.attributes) {
                tinygltf::Accessor l_accessor = l_model.accessors[l_value];
                int l_byteStride = l_accessor.ByteStride(l_model.bufferViews[l_accessor.bufferView]);
                glBindBuffer(GL_ARRAY_BUFFER, l_vbos[l_accessor.bufferView]);

                int l_size = 1;
                if (l_accessor.type != TINYGLTF_TYPE_SCALAR) {
                    l_size = l_accessor.type;
                }

                const auto &l_result = vaa.find(l_name); // map.find tries to find a POSITION vector
                if (l_result != vaa.end()) {
                    glEnableVertexAttribArray(l_result->second);
                    glVertexAttribPointer(l_result->second, l_size, l_accessor.componentType,
                                          l_accessor.normalized ? GL_TRUE : GL_FALSE,
                                          l_byteStride, OFFSET(l_accessor.byteOffset));
                } else {
                    std::cerr << "[mesh] unsupported VAA: " << l_name << std::endl;
                }
            }

            _primitives.push_back({l_primitive.mode, l_indexAccessor.count,
                                   l_indexAccessor.componentType, l_indexAccessor.byteOffset});
        }

        glBindVertexArray(0);
        for (auto &[l_key, l_value]: l_vbos) {
            glDeleteBuffers(1, &l_value);
            l_value = 0;
        }
    }


    void Mesh::Draw() const {
        glBindVertexArray(_vao);
        for (auto &l_primitive: _primitives) {
            glDrawElements(l_primitive.s_mode, l_primitive.s_count, l_primitive.s_type, OFFSET(l_primitive.s_offset));
        }
        glBindVertexArray(0);
    }


    Mesh::~Mesh() {
        for (auto &[l_key, l_value]: _buffers) {
            glDeleteBuffers(1, &l_value);
            l_value = 0;
        }
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}