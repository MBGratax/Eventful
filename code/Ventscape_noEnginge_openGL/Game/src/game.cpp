#include "game.h"

#include <glm/gtx/transform.hpp>

namespace gl3{

    game::game(fs::path assetRoot, float width, float height, const char* title) :
                        assetRoot(std::move(assetRoot)){

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

        audio.init();
        audio.setGlobalVolume(0.05f);
    }

    game::~game() {
        glfwTerminate();
    }

    void game::run() {

        auto s = std::make_unique<ship>(this);
        spaceShip = s.get();
        entities.push_back(std::move(s));

        for(int i = 0; i <100; i++){
            auto e = std::make_unique<planet>(this);
            e->getPosition() = 500.0f * glm::vec3((rand() / (float) RAND_MAX - 0.5f) * cos(glm::radians(33.0f)) * i/10 , (rand() / (float) RAND_MAX - 0.5f) * sin(glm::radians(33.0f)) * i/10, 0);
            e->getScale() = 2.0f * rand() / (float) RAND_MAX - 0.5f;
            entities.push_back(std::move(e));
        }

        for(int i = 0; i <10; i++){
            auto e = std::make_unique<enemy>(this);
            e->getPosition() = 1000.0f * glm::vec3((rand() / (float) RAND_MAX - 0.5f) * cos(glm::radians(33.0f)) * i/100 , (rand() / (float) RAND_MAX - 0.5f) * sin(glm::radians(33.0f)) * i/100, 0);
            e->getScale() = 5.0f * rand() / (float) RAND_MAX - 0.5f;
            entities.push_back(std::move(e));
        }

        backgroundSound = std::make_unique<SoLoud::Wav>();
        backgroundSound->load(resolve("audio/electronic-wave.mp3").string().c_str());
        backgroundSound->setLooping(true);
        audio.playBackground(*backgroundSound);

        // Update Loop
        while (!glfwWindowShouldClose(glfWwindow)) {

            // Update frame time
            frameTime = (float) glfwGetTime();
            glfwSetTime(0);

            // Logic Update
            update();

            // Rendering
            draw();

            // Poll for and process events
            glfwPollEvents();

            // Swap front and back buffers
            glfwSwapBuffers(glfWwindow);
        }
    }

    void game::update() {
        // Logic update
        for(auto & e : entities){
            e->update(this, frameTime);
        }

        // Exit on ESC
        if (glfwGetKey(glfWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(glfWwindow, true);
        }

    }

    void game::draw() {

        // Adjust viewport to actual window/frame buffer, not necessary equal to window size (retina!)
        int width, height;
        glfwGetFramebufferSize(glfWwindow, &width, &height);
        glViewport(0, 0, width, height);

        // Clear Render Buffer
        glClearColor(0.133f, 0.184f, 0.243f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup shader transformations
        view = glm::lookAt(glm::vec3(spaceShip->getPosition().x, spaceShip->getPosition().y, 95.0f),
                           glm::vec3(spaceShip->getPosition().x, spaceShip->getPosition().y, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));


        projection = glm::perspective(glm::radians(70.0f), viewPortWidth/viewPortHeight, 0.1f, 100.0f);

        // Draw objects
        for(auto & e : entities){
            e->draw(this);

        }
    }
}