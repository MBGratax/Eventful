#pragma once

#include <filesystem>
#include <map>

namespace Ventgame {

    struct SPrimitive {
        int s_mode;
        size_t s_count;
        int s_type;
        size_t s_offset;
    };

    class Mesh {
    public:
        explicit Mesh(const std::filesystem::path &gltfAssetPath, int meshIndex = 0);

        // delete copy constructor
        Mesh(const Mesh &other) = delete;

        Mesh(Mesh &&other) noexcept {
            std::swap(this->_buffers, other._buffers);
            std::swap(this->_primitives, other._primitives);
            std::swap(this->_vao, other._vao);
            std::swap(this->_vaa, other._vaa);
        }

        void Draw() const;

        virtual ~Mesh();

    private:
        std::map<int, unsigned int> _buffers;
        std::map<std::string, unsigned int> _vaa = {
                {"POSITION", 0},
                {"NORMAL",   1}
        };
        unsigned int _vao = 0;
        std::vector<SPrimitive> _primitives;
    };
}