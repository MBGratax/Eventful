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

        void CheckAttack();

        void CalculateVerticalMovement();

        void CalculateJumpApexModifier();

        void CalculateHorizontalMovement();

        void CalculateJumpMovement();

        void MoveCharacter();

        bool BCanUseCoyote() const{_bIsCoyoteTimeUsable && !_bIsCollidingDown && _timeLeftGrounded + _coyoteTimeThreshold > Time.time;};

        bool _bIsActive {true};
#pragma region Movement
        PlayerInputData _polledInputData {};
        float _difficulty {};
        float _currentVerticalSpeed {};
        b2Vec2 _lastPosition {};
        float _speed {50.0f};
        float _decayRate {0.01f};
#pragma endregion
#pragma region Groundchecks
        bool _bIsGrounded {false};
        bool _bIsCollidingDown {false};
        float _timeLeftGrounded {};
#pragma endregion
#pragma region Jumping
        float _jumpHeight {10.0f};
        float _currentHorizontalSpeed {};
        bool _bIsCoyoteTimeUsable {true};
        bool _bHasEndedJumpEarly {false};
        float _apexPoint {};
        float _lastJumpPressed {};
        float _jumpApexThreshold {10.0f};
        float _coyoteTimeThreshold {0.1f};
        float _jumpBuffer {0.1f};
        float _jumpEndEarlyGravityModifier {3.0f};
#pragma endregion
#pragma region Falling
        bool _bIsGravityLeft {true};
        float _minFallSpeed {80.0f};
        float _fallClamp {40.0f};
        float _maxFallSpeed {120.0f};
#pragma endregion
#pragma region Attack
        bool _bIsAttacking {false};
        b2Body* _hurtBox {};
#pragma endregion
    };
}
