#include "mesh.h"
#include "../game.h"

#include <tiny_gltf/tiny_gltf.h>

#define OFFSET(index) (void*)(index)

namespace gl3{

    template <typename T>
    GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData){
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(bufferType, buffer);
        glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);

        return buffer;
    }


    tinygltf::Model loadGltf(const std::filesystem::path &gltfAssetPath) {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err;
        std::string warn;

        bool res;
        if (gltfAssetPath.extension().string() == ".glb") {
            res = loader.LoadBinaryFromFile(&model, &err, &warn, gltfAssetPath.string());
        } else {
            res = loader.LoadASCIIFromFile(&model, &err, &warn, gltfAssetPath.string());
        }

        if (!warn.empty()) {
            std::cerr << "[tinygltf] warning: " << warn << std::endl;
        }

        if (!err.empty()) {
            std::cerr << "[tinygltf] error: " << err << std::endl;
        }

        if (!res) {
            throw std::runtime_error("[tinyglt] failed to load glTF: " + gltfAssetPath.string());
        }

        return std::move(model);
    }


    mesh::mesh(const std::filesystem::path &gltfAssetPath, int meshIndex) {
        auto model = loadGltf(gltfAssetPath);

        if (model.meshes.size() <= meshIndex) {
            throw std::runtime_error("[mesh] model does not contain requested mesh: " + gltfAssetPath.string());
        }

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::map<int, unsigned int> vbos;
        for (size_t i = 0; i < model.bufferViews.size(); ++i) {
            const auto &bufferView = model.bufferViews[i];
            const auto &buffer = model.buffers[bufferView.buffer];
            if (bufferView.target == 0) {
                std::cerr << "[mesh] bufferView.target is zero, drawArrays not supported: " << gltfAssetPath.string()
                          << std::endl;
                continue;
            }

            GLuint vbo;
            glGenBuffers(1, &vbo);
            vbos[i] = vbo;
            glBindBuffer(bufferView.target, vbo);
            glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset,
                         GL_STATIC_DRAW);
        }

        const auto &mesh = model.meshes[meshIndex];
        for (const auto &primitive : mesh.primitives) {
            const auto &indexAccessor = model.accessors[primitive.indices];
            for (const auto &attrib : primitive.attributes) {
                tinygltf::Accessor accessor = model.accessors[attrib.second];
                int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
                glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

                int size = 1;
                if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                    size = accessor.type;
                }

                const auto &result = vaa.find(attrib.first); // map.find tries to find a POSITION vector
                if (result != vaa.end()) {
                    glEnableVertexAttribArray(result->second);
                    glVertexAttribPointer(result->second, size, accessor.componentType,
                                          accessor.normalized ? GL_TRUE : GL_FALSE,
                                          byteStride, OFFSET(accessor.byteOffset));
                } else {
                    //std::cerr << "[mesh] unsupported VAA: " << attrib.first << std::endl;
                }
            }

            primitives.push_back({primitive.mode, indexAccessor.count,
                                  indexAccessor.componentType, indexAccessor.byteOffset});
        }

        glBindVertexArray(0);
        for (auto &entry : vbos) {
            glDeleteBuffers(1, &entry.second);
            entry.second = 0;
        }
    }


    void mesh::draw() const {
        glBindVertexArray(VAO);
        for (auto &primitive : primitives) {
            glDrawElements(primitive.mode, primitive.count, primitive.type, OFFSET(primitive.offset));
        }
        glBindVertexArray(0);
    }


    mesh::~mesh() {
        for (auto &entry : buffers) {
            glDeleteBuffers(1, &entry.second);
            entry.second = 0;
        }
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}