#include "Game.h"

#include <glm/gtx/transform.hpp>

namespace Ventgame {

    Game::Game(fs::path assetRoot, int width, int height, const char *title) :
            _viewPortWidth(width), _viewPortHeight(height), _assetRoot(std::move(assetRoot)) {

        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        // Make sure we get an OpenGL 4.6 context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        _glfWwindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!_glfWwindow) {
            glfwTerminate();
            throw std::runtime_error("failed to create window");
        }
        glfwSetWindowSizeLimits(_glfWwindow, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwSetWindowAspectRatio(_glfWwindow, 16, 9);

        // Set Window Icons
        std::array<std::string, 2> l_icons;
        l_icons[0] = "a";
        l_icons[1] = "b";
        glfwSetWindowIcon(_glfWwindow, 0, nullptr);

        // Enable sticky keys to not miss key events
        glfwSetInputMode(_glfWwindow, GLFW_STICKY_KEYS, GLFW_TRUE);

        // Make the window's context current
        glfwMakeContextCurrent(_glfWwindow);

        // Load GL Extensions
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        std::cout << "gpu: " << glGetString(GL_RENDERER) << std::endl
                  << "opengl version: " << glGetString(GL_VERSION) << std::endl;

        glEnable(GL_DEPTH_TEST);

        if (glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("gl error");
        }

        // Frame time (initialize to sane values)
        glfwSetTime(1.0 / 60);

        _physicsWorld = Physics::PhysicsWorld::GetInstance();
        b2BodyDef l_groundBodyDef;
        l_groundBodyDef.position.Set(-50.0f, -10.0f);
        _groundBody = _physicsWorld->CreateBody(l_groundBodyDef);

        b2PolygonShape l_groundBox;
        l_groundBox.SetAsBox(100.0f, 1.0f);
        _groundBody->CreateFixture(&l_groundBox, 0.0f);
    }

    Game::~Game() {
        glfwTerminate();
    }

    void Game::Run() {
        // Init Game Objects and add them to entity vector

        // Update Loop
        while (!glfwWindowShouldClose(_glfWwindow)) {

            // Logic Update
            Update();

            //Physics Update
            PhysicsUpdate();

            // Rendering
            Draw();

            // Swap front and back buffers
            glfwSwapBuffers(_glfWwindow);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    void Game::Update() {

        _frameTime = (float) glfwGetTime();

        // Logic update
        for (const auto &l_e: _entities) {
            l_e->Update(this, _frameTime);
        }

        // Exit on ESC
        if (glfwGetKey(_glfWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(_glfWwindow, true);
        }

    }

    void Game::PhysicsUpdate() {
        _physicsWorld->Step();
    }

    void Game::Draw() {

        // Adjust viewport to actual window/frame buffer, not necessary equal to window size (retina!)
        int l_width;
        int l_height;
        glfwGetFramebufferSize(_glfWwindow, &l_width, &l_height);
        glViewport(0, 0, l_width, l_height);

        // Clear Render Buffer
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup shader transformations
        _view = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f),
                            glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));


        _projection = glm::perspective(glm::radians(15.0f), (float) _viewPortWidth / (float) _viewPortHeight, 0.1f,
                                       100.0f);

        // Draw objects
        for (const auto &l_e: _entities) {
            l_e->Draw(this);
        }

    }
}