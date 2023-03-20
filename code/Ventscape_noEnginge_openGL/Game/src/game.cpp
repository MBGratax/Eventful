#include "game.h"

#include <glm/gtx/transform.hpp>

namespace Ventgame{

    game::game(fs::path assetRoot, int width, int height, const char* title) :
            viewPortWidth(width), viewPortHeight(height),assetRoot(std::move(assetRoot)){

        if(!glfwInit()){
            throw std::runtime_error("Failed to initialize GLFW");
        }

        // Make sure we get an OpenGL 4.6 context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        glfWwindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!glfWwindow) {
            glfwTerminate();
            throw std::runtime_error("failed to create window");
        }
        glfwSetWindowSizeLimits(glfWwindow, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwSetWindowAspectRatio(glfWwindow, 16, 9);

        // Set Window Icons
        std::array<std::string , 2> Licons;
        Licons[0] = "a";
        Licons[1] = "b";
        glfwSetWindowIcon(glfWwindow, 0, nullptr);

        // Enable sticky keys to not miss key events
        glfwSetInputMode(glfWwindow, GLFW_STICKY_KEYS, GLFW_TRUE);

        // Make the window's context current
        glfwMakeContextCurrent(glfWwindow);

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

        physicsWorld = physics::PhysicsWorld::GetInstance();
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(-50.0f, -10.0f);
        groundBody = physicsWorld->CreateBody(groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(100.0f, 1.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    game::~game() {
        glfwTerminate();
    }

    void game::run() {
        // Init Game Objects and add them to entity vector

        // Update Loop
        while (!glfwWindowShouldClose(glfWwindow)) {

            // Logic Update
            update();

            //Physics Update
            PhysicsUpdate();

            // Rendering
            draw();

            // Swap front and back buffers
            glfwSwapBuffers(glfWwindow);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    void game::update() {

        frameTime = (float) glfwGetTime();

        // Logic update
        for(const auto & e : entities){
            e->update(this, frameTime);
        }

        // Exit on ESC
        if (glfwGetKey(glfWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(glfWwindow, true);
        }

    }

    void game::PhysicsUpdate() {
        physicsWorld->Step();
    }

    void game::draw() {

        // Adjust viewport to actual window/frame buffer, not necessary equal to window size (retina!)
        int width;
        int height;
        glfwGetFramebufferSize(glfWwindow, &width, &height);
        glViewport(0, 0, width, height);

        // Clear Render Buffer
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup shader transformations
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));


        projection = glm::perspective(glm::radians(15.0f), (float)viewPortWidth/(float)viewPortHeight, 0.1f, 100.0f);

        // Draw objects
        for(const auto & e : entities) {
            e->draw(this);
        }

    }
}