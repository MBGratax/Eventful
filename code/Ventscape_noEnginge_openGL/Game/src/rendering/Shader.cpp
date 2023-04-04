#include "Shader.h"
#include "../Game.h"

#include <glm/gtc/type_ptr.hpp>

namespace Ventgame {

    std::string readText(const std::filesystem::path &fileName) {
        std::ifstream l_sourceFile(fileName);
        std::stringstream l_buffer;
        l_buffer << l_sourceFile.rdbuf();
        return l_buffer.str();
    }

    struct SGlStatusData {
        int s_success;
        const char *s_shaderName;
        char s_infoLog[GL_INFO_LOG_LENGTH];
    };

    unsigned int loadAndCompileShader(GLuint shaderType, const fs::path &shaderAssetPath) {

        unsigned int l_shader = glCreateShader(shaderType);
        auto l_shaderSrc = readText(shaderAssetPath);
        const char *l_shaderSource = l_shaderSrc.c_str();

        glShaderSource(l_shader, 1, &l_shaderSource, nullptr);
        glCompileShader(l_shader);

        {
            SGlStatusData l_compilationStatus{};

            if (shaderType == GL_VERTEX_SHADER) l_compilationStatus.s_shaderName = "VERTEX";
            if (shaderType == GL_FRAGMENT_SHADER) l_compilationStatus.s_shaderName = "FRAGMENT";

            glGetShaderiv(l_shader, GL_COMPILE_STATUS, &l_compilationStatus.s_success);
            if (l_compilationStatus.s_success == GL_FALSE) {
                glGetShaderInfoLog(l_shader, GL_INFO_LOG_LENGTH, nullptr, l_compilationStatus.s_infoLog);
                throw std::runtime_error("ERROR::SHADER::" + std::string(l_compilationStatus.s_shaderName)
                                         + "::COMPILATION_FAILED\n"
                                         + std::string(l_compilationStatus.s_infoLog));
            }
        }

        return l_shader;
    }

    Shader::Shader(const fs::path &vertexShaderAsset, const fs::path &fragmentShaderAsset) {

        _vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderAsset);
        _fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderAsset);

        _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShader);
        glAttachShader(_shaderProgram, _fragmentShader);
        glLinkProgram(_shaderProgram);

        {
            SGlStatusData l_linkingStatus{};
            glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &l_linkingStatus.s_success);
            if (l_linkingStatus.s_success == GL_FALSE) {
                glGetShaderInfoLog(_shaderProgram, GL_INFO_LOG_LENGTH, nullptr, l_linkingStatus.s_infoLog);
                throw std::runtime_error("ERROR::PROGRAM::LINKING_FAILED\n" + std::string(l_linkingStatus.s_infoLog));
            }
        }

        glDetachShader(_shaderProgram, _vertexShader);
        glDetachShader(_shaderProgram, _fragmentShader);
    }


    void Shader::Use() const {
        glUseProgram(_shaderProgram);
    }

    void Shader::SetMatrix(const std::string &uniform, glm::mat4 matrix) const {
        unsigned l_uniformLocation = glGetUniformLocation(_shaderProgram, uniform.c_str());
        glUniformMatrix4fv(l_uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetVector(const std::string &uniform, glm::vec4 vector) const {
        unsigned l_uniformLocation = glGetUniformLocation(_shaderProgram, uniform.c_str());
        glUniform4fv(l_uniformLocation, 1, glm::value_ptr(vector));
    }

    Shader::~Shader() {
        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);
    }
}