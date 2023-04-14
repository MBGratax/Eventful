
#include "PlayerCharacter.h"
#include "../Game.h"

namespace Ventgame {

    PlayerCharacter::PlayerCharacter(glm::vec3 position, float zRotation, float scale, glm::vec4 const &colour)
            : Entity(
            Shader("Shaders/FlatcolourVertexShader.glsl", "Shaders/FlatColourFragmentShader.glsl"),
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
        /* TODO: Make player move upwards based on difficulty
         * TODO: Make player jump based on button press duration
         * TODO: Make player change gravity based on button press
         * TODO: Make player attack based on button press
         */
    }

    b2Body *
    PlayerCharacter::CreatePlayerBody(b2Vec2 position, float size, float angle,
                                      PlayerCharacter const *playerCharacter) {
        return nullptr;
    }
}