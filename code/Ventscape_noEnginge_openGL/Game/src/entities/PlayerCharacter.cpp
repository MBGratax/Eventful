
#include "PlayerCharacter.h"
#include "../Game.h"
#include "../Asset.h"

namespace Ventgame {

    PlayerCharacter::PlayerCharacter(glm::vec3 position, float zRotation, float scale, glm::vec4 const &colour)
            : Entity(
            Shader("Shaders/FlatcolourVertexShader.glsl", "Shaders/FlatColourFragmentShader.glsl"),
            Mesh("Meshes/Box.glb"),
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
        b2BodyDef l_bodyDef;
        // User Data
        l_bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(playerCharacter);
        l_bodyDef.type = b2_dynamicBody;
        l_bodyDef.position = position;
        l_bodyDef.angle = angle;
        b2Body *l_body = Physics::PhysicsWorld::GetInstance()->CreateBody(l_bodyDef);
        b2Vec2 l_vertices[6];
        l_vertices[0].Set(0.5f, 0.025f);
        l_vertices[1].Set(0.0f, 0.3f);
        l_vertices[2].Set(-0.2f, 0.05f);
        l_vertices[3].Set(0.5f, -0.025f);
        l_vertices[4].Set(0.0f, -0.3f);
        l_vertices[5].Set(-0.2f, -0.05f);
        for (auto &l_point : l_vertices) {
            l_point *= size;
        }
        b2PolygonShape l_boxShape;
        l_boxShape.Set(l_vertices, 6);
        b2FixtureDef l_fixtureDef;
        l_fixtureDef.shape = &l_boxShape;
        l_fixtureDef.density = 1;
        l_fixtureDef.friction = 0.1f;
        l_fixtureDef.restitution = 0.1f;
        l_body->CreateFixture(&l_fixtureDef);
        l_body->SetFixedRotation(true);
        return l_body;

    }
}