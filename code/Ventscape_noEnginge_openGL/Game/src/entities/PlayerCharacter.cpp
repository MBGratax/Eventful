
#include "PlayerCharacter.h"
#include "../game.h"

namespace Ventgame {

    PlayerCharacter::PlayerCharacter(glm::vec3 position, float zRotation, float scale, glm::vec4 colour) : entity(
            shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl"),
            mesh("Meshes"),
            position,
            zRotation,
            scale,
            colour,
            createPlayerBody({position.x,position.y},scale,glm::radians(zRotation), this)) {

    }

    void PlayerCharacter::startContact() {
        entity::startContact();
    }

    void PlayerCharacter::draw(game *game) {
        entity::draw(game);
    }

    void PlayerCharacter::update(game *game, float deltaTime) {
        entity::update(game,deltaTime);
    }

    b2Body *
    PlayerCharacter::createPlayerBody(b2Vec2 position, float size, float angle, PlayerCharacter *playerCharacter) {
        return nullptr;
    }
}