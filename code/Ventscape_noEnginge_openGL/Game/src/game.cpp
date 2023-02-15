#include "game.h"

#include <glm/gtx/transform.hpp>

namespace Ventgame{

    //ToDo init physics world
    game::game(fs::path assetRoot, float width, float height, const char* title) :
            assetRoot(std::move(assetRoot)), physicsWorld({0.0f, 0.0f}){

        viewPortWidth = width;
        viewPortHeight = height;

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

//        audio.init();
//        audio.setGlobalVolume(0.1f);

        //ToDo: add ground
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(-50.0f, -10.0f);
        groundBody = physicsWorld.CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(100.0f, 1.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    game::~game() {
        glfwTerminate();
    }

    void game::run() {

        //b2Vec2 physicsPosShip(0.0f, 0.0f);
        //auto s = std::make_unique<ship>(this, physicsPosShip);
        //spaceShip = s.get();
        //entities.push_back(std::move(s));

        // Generate planets
        //for(int i = 0; i <100; i++){
        //    //ToDo: init physic body
        //    auto initPos = 100.0f * glm::vec3((rand() / (float) RAND_MAX - 0.5f) * cos(glm::radians(33.0f)) * i/10 , (rand() / (float) RAND_MAX - 0.5f) * sin(glm::radians(33.0f)) * i/10, 0);
        //    b2Vec2 physicsPos = {initPos.x, initPos.y};
        //    auto e = std::make_unique<planet>(this, physicsPos);
        //    e->getPosition() = initPos;
        //    e->getScale() = 2.0f * rand() / (float) RAND_MAX - 0.5f;
        //    entities.push_back(std::move(e));
        //}

        // Play Background Sound
        //backgroundSound = std::make_unique<SoLoud::Wav>();
        //backgroundSound->load(resolve("audio/electronic-wave.mp3").string().c_str());
        //backgroundSound->setLooping(true);
        //audio.playBackground(*backgroundSound);

        // Update Loop
        while (!glfwWindowShouldClose(glfWwindow)) {

            // Logic Update
            update();

            //Physics Update
            physics();

            // Rendering
            draw();

            // Poll for and process events
            glfwPollEvents();

            // Swap front and back buffers
            glfwSwapBuffers(glfWwindow);
        }
    }

    void game::update() {

        frameTime = (float) glfwGetTime();

        // Logic update
        for(auto & e : entities){
            e->update(this, frameTime);
        }

        // Exit on ESC
        if (glfwGetKey(glfWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(glfWwindow, true);
        }

    }

    void game::physics() {
        const int32 velocityIterations = 6;
        const int32 positionIterations = 2;
        const float timeStep = 1.0f / 60.0f;
        physicsWorld.Step(timeStep, velocityIterations, positionIterations);
    }

    void game::draw() {

        // Adjust viewport to actual window/frame buffer, not necessary equal to window size (retina!)
        int width, height;
        glfwGetFramebufferSize(glfWwindow, &width, &height);
        glViewport(0, 0, width, height);

        // Clear Render Buffer
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup shader transformations
        //view = glm::lookAt(glm::vec3(spaceShip->getPosition().x, spaceShip->getPosition().y, 15.0f),
        //                   glm::vec3(spaceShip->getPosition().x, spaceShip->getPosition().y, 0.0f),
        //                   glm::vec3(0.0f, 1.0f, 0.0f));


        projection = glm::perspective(glm::radians(15.0f), viewPortWidth/viewPortHeight, 0.1f, 100.0f);

        // Draw objects
        for(auto & e : entities) {
            e->draw(this);
        }

    }
}