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

        virtual ~entity();

        virtual void update(game *game, float frameTime) = 0;

        virtual void draw(game *game);

        virtual void startContact() {
            //Comment to remove linting notification
        };

        [[nodiscard]] const glm::vec3 &getPosition() const {return position; }
        [[nodiscard]] float getZRotation() const { return zRotation; }
        [[nodiscard]] const glm::vec3 &getScale() const { return scale; }
        [[nodiscard]] const glm::vec4 &getColor() const {return  color;}
        void setPosition(const glm::vec3 &position) { entity::position = position; }
        void setZRotation(float zRotation) { entity::zRotation = zRotation; }
        void setScale(const glm::vec3 &scale) { entity::scale = scale; }
        b2Body* &getBody(){return body;}


        void setXPos(float x) { position.x = x;}
        void setYPos(float y) { position.y = y;}

        float &getZRotation() {return zRotation;}
        void setZRot(float z) { zRotation = z;}

        float &getDeltaTime() {return deltaTime;}
        float &getLastFrame() {return lastFrame;}

    private:
        glm::vec3 position;
        float zRotation;
        glm::vec3 scale;
        glm::vec4 color;
        shader myShader;
        mesh myMesh;
        b2Body *body;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    };
}