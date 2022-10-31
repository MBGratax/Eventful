#pragma once

#include <filesystem>
#include <map>

namespace Ventgame{

    struct primitive {
        int mode;
        size_t count;
        int type;
        size_t offset;
    };

    class mesh {
    public:
        explicit mesh(const std::filesystem::path &gltfAssetPath, int meshIndex = 0);

        // delete copy constructor
        mesh(const mesh &other) = delete;

        mesh(mesh &&other) noexcept {
            std::swap(this->buffers, other.buffers);
            std::swap(this->primitives, other.primitives);
            std::swap(this->VAO, other.VAO);
        }

        void draw() const;

        ~mesh();
    private:
        std::map<int, unsigned int> buffers;
        std::map<std::string, unsigned int> vaa = {{"POSITION", 0}, {"NORMAL", 1}};
        unsigned int VAO = 0;
        std::vector<primitive> primitives;
    };
}