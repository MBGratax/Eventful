#include "shader.h"
#include "../game.h"

#include <glm/gtc/type_ptr.hpp>

namespace Ventgame{

    std::string readText(const std::filesystem::path &fileName) {
        std::ifstream sourceFile(fileName);
        std::stringstream buffer;
        buffer << sourceFile.rdbuf();
        return buffer.str();
    }

    struct glStatusData {
        int success;
        const char* shaderName;
        char infoLog[GL_INFO_LOG_LENGTH];
    };

    unsigned int loadAndCompileShader(GLuint shaderType, const fs::path &shaderAssetPath){

        unsigned int shader = glCreateShader(shaderType);
        auto shaderSrc = readText(shaderAssetPath);
        const char* shaderSource = shaderSrc.c_str();

        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);

        {
            glStatusData compilationStatus{};

            if(shaderType == GL_VERTEX_SHADER) compilationStatus.shaderName = "VERTEX";
            if(shaderType == GL_FRAGMENT_SHADER) compilationStatus.shaderName = "FRAGMENT";

            glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus.success);
            if(compilationStatus.success == GL_FALSE){
                glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
                throw std::runtime_error("ERROR::SHADER::" + std::string(compilationStatus.shaderName)
                                                           + "::COMPILATION_FAILED\n"
                                                           + std::string(compilationStatus.infoLog));
            }
        }

        return shader;
    }

    shader::shader(const fs::path &vertexShaderAsset, const fs::path &fragmentShaderAsset) {

        vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderAsset);
        fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderAsset);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        {
            glStatusData linkingStatus{};
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingStatus.success);
            if(linkingStatus.success == GL_FALSE){
                glGetShaderInfoLog(shaderProgram, GL_INFO_LOG_LENGTH, nullptr, linkingStatus.infoLog);
                throw std::runtime_error("ERROR::PROGRAM::LINKING_FAILED\n" + std::string(linkingStatus.infoLog));
            }
        }

        glDetachShader(shaderProgram, vertexShader);
        glDetachShader(shaderProgram, fragmentShader);
    }


    void shader::use() const {
        glUseProgram(shaderProgram);
    }

    void shader::setMatrix(const std::string &uniform, glm::mat4 matrix) const{
        unsigned uniformLocation = glGetUniformLocation(shaderProgram, uniform.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void shader::setVector(const std::string &uniform, glm::vec4 vector) const{
        unsigned uniformLocation = glGetUniformLocation(shaderProgram, uniform.c_str());
        glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
    }

    shader::~shader() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}