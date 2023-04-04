
#include "PhysicsWorld.h"

namespace Ventgame::Physics {

    b2Body *PhysicsWorld::CreateBody(const b2BodyDef &bodyDef) {
        return _b2->CreateBody(&bodyDef);
    }

    PhysicsWorld *PhysicsWorld::GetInstance() {
        if (_instance == nullptr) {
            _instance = new PhysicsWorld();
        }
        return _instance;
    }

    PhysicsWorld::PhysicsWorld() {
        _b2 = std::make_unique<b2World>(_gravity);
        _b2->SetContactListener(&_listenerInstance);
    }

}
