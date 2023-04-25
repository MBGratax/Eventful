#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace Ventgame {
    class Game;

    namespace fs = std::filesystem;

    class Shader {
    public:

        Shader(const fs::path &vertexShaderAsset, const fs::path &fragmentShaderAsset);

        // delete copy constructor
        Shader(const Shader &shader) = delete;

        // explicit move constructor
        Shader(Shader &&other) noexcept {
            std::swap(this->_shaderProgram, other._shaderProgram);
            std::swap(this->_vertexShader, other._vertexShader);
            std::swap(this->_fragmentShader, other._fragmentShader);
        }

        void Use() const;

        void SetMatrix(const std::string &uniform, glm::mat4 matrix) const;

        void SetVector(const std::string &uniform, glm::vec4 vector) const;

        ~Shader();

    private:
        unsigned int _shaderProgram = 0;
        unsigned int _vertexShader = 0;
        unsigned int _fragmentShader = 0;

        unsigned int LoadAndCompileShader(unsigned int shaderType, const fs::path &shaderAssetPath);

        std::string ReadText(const std::filesystem::path &fileName);
    };
}