#pragma once

#include <filesystem>
#include <map>

namespace gl3{

    struct primitive {
        int mode;
        size_t count;
        int type;
        size_t offset;
    };

    class mesh {
    public:
        //mesh::mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        mesh(const std::filesystem::path &gltfAssetPath, int meshIndex = 0);

        // delete copy constructor
        mesh(const mesh &other) = delete;

        // explicit move constructor
        mesh(mesh &&other) noexcept {
            std::swap(this->buffers, other.buffers);
            std::swap(this->primitives, other.primitives);
            std::swap(this->VAO, other.VAO);
        }

        void draw() const;

        ~mesh();
    private:

        unsigned int VAO = 0;
        std::map<int, unsigned int> buffers;
        std::map<std::string, unsigned int> vaa = {{"POSITION", 0},
                                                   {"NORMAL",   1}};
        std::vector<primitive> primitives;
    };
}