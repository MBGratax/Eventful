#pragma once

#include <memory>
#include <filesystem>
#include <iostream>
#include <vector>
#include <array>

#include <windows.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <box2d/box2d.h>

#include "entities/Entity.h"
#include "physics/PhysicsWorld.h"

namespace Ventgame {
    namespace fs = std::filesystem;

    class Game {
    public:
        explicit Game(fs::path assetRoot = "./assets", int width = 800, int height = 600,
                      const char *title = "GameLabIII");

        ~Game();

        void Run();

        glm::mat4 &GetViewMatrix() { return _view; }

        glm::mat4 &GetProjectionMatrix() { return _projection; }

        [[nodiscard]] GLFWwindow *GetWindow() const { return _glfWwindow; }

        [[nodiscard]] fs::path Resolve(const fs::path &relativeAssetPath) const {

            return fs::canonical((_assetRoot / relativeAssetPath).make_preferred());
        }


        auto &GetPhysicsWorld() { return _physicsWorld; }

        const float &GetDifficulty() const { return _difficulty; }

    private:
        void Update();

        void PhysicsUpdate();

        void Draw();

        GLFWwindow *_glfWwindow = nullptr;
        float _frameTime = 1.0f / 60.0f;

        glm::mat4 _view = glm::mat4(1.0f);
        glm::mat4 _projection = glm::mat4(1.0f);
        int _viewPortWidth = 0;
        int _viewPortHeight = 0;
        float _difficulty = 1.0f;

        std::vector<std::unique_ptr<Entity>> _entities;

        std::filesystem::path _assetRoot;

        Physics::PhysicsWorld *_physicsWorld = Physics::PhysicsWorld::GetInstance();
        b2Body *_groundBody = nullptr;

    };
}