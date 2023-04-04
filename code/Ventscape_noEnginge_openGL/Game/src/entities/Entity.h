#pragma once

#include "../rendering/Shader.h"
#include "../rendering/Mesh.h"
#include <box2d/box2d.h>

namespace Ventgame {

    class Entity {
    public:
        Entity(Shader shader,
               Mesh mesh,
               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float zRotation = 0.0f,
               float scale = 1.0f,
               const glm::vec4 &color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
               b2Body *body = nullptr);

        virtual ~Entity();

        virtual void Update(Game *game, float frameTime) = 0;

        virtual void Draw(Game *game);

        virtual void StartContact() {
            //Comment to remove linting notification
        };

        void SetPosition(const glm::vec3 &position) { Entity::_position = position; }

        void SetZRotation(float zRotation) { Entity::_zRotation = zRotation; }

        void SetScale(const glm::vec3 &scale) { Entity::_scale = scale; }

        b2Body *&GetBody() { return _body; }


        void SetXPos(float x) { _position.x = x; }

        void SetYPos(float y) { _position.y = y; }

        float &GetZRotation() { return _zRotation; }

        void SetZRot(float z) { _zRotation = z; }

        float &GetDeltaTime() { return _deltaTime; }

        float &GetLastFrame() { return _lastFrame; }

    private:
        glm::vec3 _position;
        float _zRotation;
        glm::vec3 _scale;
        glm::vec4 _color;
        Shader _myShader;
        Mesh _myMesh;
        b2Body *_body;
        float _deltaTime = 0.0f;
        float _lastFrame = 0.0f;
    };
}