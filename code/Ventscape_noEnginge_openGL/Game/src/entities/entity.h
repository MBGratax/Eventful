#pragma once

#include "../rendering/shader.h"
#include "../rendering/mesh.h"
#include <box2d/box2d.h>

namespace Ventgame {

    class entity {
    public:
        entity(shader shader,
               mesh mesh,
               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float zRotation = 0.0f,
               float scale = 1.0f,
               const glm::vec4& color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
               b2Body *body = nullptr);

        virtual ~entity() = default;

        virtual void update(game *game, float frameTime) = 0;

        virtual void draw(game *game);

        glm::vec3 &getPosition() {return position;}
        float &getScale() {return scale;}
        glm::vec4 &getColor() {return color;}

        void setXPos(float x) { position.x = x;}
        void setYPos(float y) { position.y = y;}

        float &getZRotation() {return zRotation;}
        void setZRot(float z) { zRotation = z;}

        float &getDeltaTime() {return deltaTime;}
        float &getLastFrame() {return lastFrame;}

        auto &getBody() {return body;}

    private:
        glm::vec3 position;
        float zRotation;
        float scale = 1.0f;
        glm::vec4 color;

        shader myShader;
        mesh myMesh;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        b2Body *body = nullptr;
    };
}