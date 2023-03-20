

#include "entity.h"

namespace Ventgame {

    class PlayerCharacter : public entity {

    public:
        explicit PlayerCharacter(game *game, glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
                                 float zRotation = 0.0f,
                                 float scale = 1.0f,
                                 glm::vec4 colour = {1.0f,1.0f,1.0f,1.0f});
        void update(game *game, float deltaTime) override;
        void draw(game *game) override;
        void startContact() override;
        b2Body *createPlayerBody(b2Vec2 position, float size, float angle, PlayerCharacter* playerCharacter);
    private:
        float _speed = 50.0f;
        float _jumpHeight = 10;
        b2Body* hurtBox;
        bool _bIsAttacking = false;
        bool _bIsJumping = false;
        bool _bIsGravityLeft = true;

    };

}

