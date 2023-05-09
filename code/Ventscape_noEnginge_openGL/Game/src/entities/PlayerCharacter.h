#pragma once

#include "Entity.h"

namespace Ventgame {

    struct PlayerInputData{
        bool bJumpPressed = false;
        bool bJumpReleased = false;
        bool bAttackPressed = false;
        bool bGravityPressed = false;
    };

    class PlayerCharacter : public Entity {

    public:
        explicit PlayerCharacter(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                                 float zRotation = 0.0f,
                                 float scale = 1.0f,
                                 glm::vec4 const &colour = {1.0f, 1.0f, 1.0f, 1.0f});

        void Update(Game *game, float deltaTime) override;

        void Draw(Game *game) override;

        void StartContact() override;

        static b2Body *CreatePlayerBody(b2Vec2 position, float size, float angle, PlayerCharacter const *playerCharacter);
    private:
        void PollInputs(Game const *game);
    private:
        PlayerInputData _polledInputData;
        float _speed = 50.0f;
        float _decayrate = 0.01f;
        float _jumpHeight = 10;
        b2Body* _hurtBox;
        bool _bIsAttacking = false;
        bool _bIsGrounded = false;
        bool _bIsGravityLeft = true;

        void CheckAttack();

        void CalculateVerticalMovement();

        void CalculateJumpApexModifier();

        void CalculateHorizontalMovement();

        void CalculateJumpMovement();

        void MoveCharacter();

        float _difficulty;
    };

}

