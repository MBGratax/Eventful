#include "entity.h"
#include "../game.h"
#include <string>
#include <glm/gtx/transform.hpp>

namespace Ventgame{

    entity::entity(shader shader, mesh mesh, glm::vec3 position, float zRotation, float scale, const glm::vec4& color, b2Body *body) :
            position(position), zRotation(zRotation), scale(scale), color(color),myShader(std::move(shader)), myMesh(std::move(mesh)),  body(body) {};

    void entity::draw(game *game) {

        auto physicPosition = body->GetPosition();
        position.x = physicPosition.x;
        position.y = physicPosition.y;

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
        model = glm::rotate(model, glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale));


        myShader.use();
        myShader.setMatrix("model", model);
        myShader.setMatrix("view", game->getViewMatrix());
        myShader.setMatrix("projection", game->getProjectionMatrix());
        myShader.setMatrix("modelToWorldNormal", glm::transpose(glm::inverse(model)));
        myShader.setVector("color", color);

        myMesh.draw();
    }

    entity::~entity(){
        body->GetWorld()->DestroyBody(body);
    }
}