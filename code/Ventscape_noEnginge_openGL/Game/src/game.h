#pragma once

#include <memory>
#include <filesystem>
#include <iostream>
#include <vector>

#include <windows.h>

#include <glm/mat4x4.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include <soloud.h>
//#include <soloud_wav.h>

#include <box2d/box2d.h>

#include "entities/entity.h"

namespace Ventgame{
    namespace fs = std::filesystem;

    class game {
    public:
        explicit game(fs::path assetRoot = "./assets", float width = 800.0f, float height = 600.0f, const char* title = "GameLabIII");

        ~game();

        void run();

        glm::mat4 &getViewMatrix() { return view; }
        glm::mat4 &getProjectionMatrix() { return projection; }
        [[nodiscard]] GLFWwindow *getWindow() const { return glfWwindow; }

        [[nodiscard]] fs::path resolve(const fs::path &relativeAssetPath) const {

            return fs::canonical((assetRoot / relativeAssetPath).make_preferred());
        }

        //auto &getAudio(){return audio;}

        auto &getPhysicsWorld() {return physicsWorld;}

    private:
        void update();
        void physics();
        void draw();

        GLFWwindow *glfWwindow = nullptr;
        float frameTime = 1.0 / 60.0;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        float viewPortWidth = 0;
        float viewPortHeight = 0;

        std::vector<std::unique_ptr<entity>> entities;

        std::filesystem::path assetRoot;

//        SoLoud::Soloud audio;
//        std::unique_ptr<SoLoud::Wav> backgroundSound;

        b2World physicsWorld;
        b2Body *groundBody = nullptr;

    };
}