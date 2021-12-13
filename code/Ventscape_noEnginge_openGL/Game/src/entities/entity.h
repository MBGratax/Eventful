#pragma once

#include "../rendering/shader.h"
#include "../rendering/mesh.h"

#include <glm/vec3.hpp>

namespace gl3 {

    class entity {
    public:
        entity(shader shader,
               mesh mesh,
               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float zRotation = 0.0f,
               float scale = 1.0f,
               glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        virtual ~entity() = default;

        virtual void update(game *game, float frameTime) {};

        virtual void draw(game *game);

        glm::vec3 &getPosition() {return position;}
        float &getScale() {return scale;}
        glm::vec4 &getColor() {return color;}

        void setXPos(float x) { position.x = x;}
        void setYPos(float y) { position.y = y;}

        float &getZRotation() {return zRotation;}
        void setZRot(float z) { zRotation = z;}

    private:
        glm::vec3 position;
        float zRotation;
        float scale = 1.0f;
        glm::vec4 color;

        shader myShader;
        mesh myMesh;

    };
}
