
#include "PlayerCharacter.h"
#include "../Game.h"
#include "Entity.h"

namespace Ventgame {

    PlayerCharacter::PlayerCharacter(glm::vec3 position, float zRotation, float scale, glm::vec4 const &colour)
            : Entity(
            Shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl"),
            Mesh("Meshes"),
            position,
            zRotation,
            scale,
            colour,
            CreatePlayerBody({position.x, position.y}, scale, glm::radians(zRotation), this)) {

    }

    void PlayerCharacter::StartContact() {
        Entity::StartContact();
    }

    void PlayerCharacter::Draw(Game *game) {
        Entity::Draw(game);
    }

    void PlayerCharacter::Update(Game *game, float deltaTime) {
    }

    b2Body *
    PlayerCharacter::CreatePlayerBody(b2Vec2 position, float size, float angle,
                                      PlayerCharacter const *playerCharacter) {
        return nullptr;
    }
}