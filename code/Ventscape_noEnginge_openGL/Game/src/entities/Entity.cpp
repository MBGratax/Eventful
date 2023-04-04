#include "../Game.h"
#include <string>
#include <glm/gtx/transform.hpp>

namespace Ventgame {

    Entity::Entity(Shader shader, Mesh mesh, glm::vec3 position, float zRotation, float scale, const glm::vec4 &color,
                   b2Body *body) :
            _position(position), _zRotation(zRotation), _scale(scale), _color(color), _myShader(std::move(shader)),
            _myMesh(std::move(mesh)), _body(body) {};

    void Entity::Draw(Game *game) {

        auto l_physicPosition = _body->GetPosition();
        _position.x = l_physicPosition.x;
        _position.y = l_physicPosition.y;

        auto l_model = glm::mat4(1.0f);
        l_model = glm::translate(l_model, glm::vec3(_position.x, _position.y, _position.z));
        l_model = glm::rotate(l_model, glm::radians(_zRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        l_model = glm::scale(l_model, glm::vec3(_scale));


        _myShader.Use();
        _myShader.SetMatrix("model", l_model);
        _myShader.SetMatrix("view", game->GetViewMatrix());
        _myShader.SetMatrix("projection", game->GetProjectionMatrix());
        _myShader.SetMatrix("modelToWorldNormal", glm::transpose(glm::inverse(l_model)));
        _myShader.SetVector("color", _color);

        _myMesh.Draw();
    }

    Entity::~Entity() {
        _body->GetWorld()->DestroyBody(_body);
    }
}