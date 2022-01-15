#include "entity.h"
#include "../game.h"
#include <string>
#include <glm/gtx/transform.hpp>

namespace gl3{

    entity::entity(shader shader, mesh mesh, glm::vec3 position, float zRotation, float scale, glm::vec4 color, b2Body *body) :
    myShader(std::move(shader)), myMesh(std::move(mesh)), position(position), zRotation(zRotation), scale(scale), color(color), body(body) {};

    void entity::draw(game *game) {

        auto physicPosition = body->GetPosition();
        getPosition().x = physicPosition.x;
        getPosition().y = physicPosition.y;

        glm::mat4 model = glm::mat4(1.0f);
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
}