
#include "PlayerCharacter.h"
#include "../Game.h"
#include "../Asset.h"

namespace Ventgame {

    std::ostream & operator<<(std::ostream & Str, PlayerInputData const & v) {
        Str << "Jump Pressed: " << v.bJumpPressed << " Jump Released: " << v.bJumpReleased << " Attack Pressed: " << v.bAttackPressed << " Gravity Pressed: " << v.bGravityPressed;
        return Str;
    }
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

        _difficulty = game->GetDifficulty();
        PollInputs(game);
        CheckAttack();

        CalculateVerticalMovement();
        CalculateJumpApexModifier();
        CalculateHorizontalMovement();
        CalculateJumpMovement();

        MoveCharacter();
    }

    b2Body *
    PlayerCharacter::CreatePlayerBody(b2Vec2 position, float size, float angle,
                                      PlayerCharacter const *playerCharacter) {
        b2BodyDef l_bodyDef;
        // User Data
        l_bodyDef.userData.pointer = std::bit_cast<uintptr_t>(playerCharacter);
        l_bodyDef.type = b2_dynamicBody;
        l_bodyDef.position = position;
        l_bodyDef.angle = angle;
        b2Body *l_body = Physics::PhysicsWorld::GetInstance().CreateBody(l_bodyDef);
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

    void PlayerCharacter::PollInputs(Game const *game) {
        GLFWwindow *l_window = game->GetWindow();
        _polledInputData.bJumpPressed = glfwGetKey(l_window, GLFW_KEY_SPACE);
        _polledInputData.bJumpReleased = !_polledInputData.bJumpPressed;
        _polledInputData.bAttackPressed = glfwGetKey(l_window, GLFW_KEY_A);
        _polledInputData.bGravityPressed = glfwGetKey(l_window, GLFW_KEY_D);
    }

    void PlayerCharacter::CheckAttack() {
        if(_polledInputData.bAttackPressed && !_bIsAttacking) {
            _bIsAttacking = true;
        }
        // TODO: If Attack is pressed, and the player is not already attacking, activate hurtbox and perform attack for duration
    }

    void PlayerCharacter::CalculateVerticalMovement() {
        // TODO: Move up with velocity, decrease with decayrate, update decayrate based on difficulty
    }

    void PlayerCharacter::CalculateJumpApexModifier() {
        // TODO: Update jump apex based on current position to make the jump a nice and smooth curve
    }

    void PlayerCharacter::CalculateHorizontalMovement() {
        // TODO: Make gravity calculations. Change gravity based on _bGravityIsLeft
    }

    void PlayerCharacter::CalculateJumpMovement() {
        // TODO:Update jump related variables, such as coyote time
    }

    void PlayerCharacter::MoveCharacter() {
        // TODO: Based on previous calculations, attempt to move character to appropriate position based on collision
    }
}