
#include "PhysicsWorld.h"
#include <iostream>

namespace Ventgame::Physics {

    b2Body *PhysicsWorld::CreateBody(const b2BodyDef &bodyDef) {
        return _b2->CreateBody(&bodyDef);
    }

    PhysicsWorld::PhysicsWorld() {
        _b2 = std::make_unique<b2World>(_gravity);
        _b2->SetContactListener(&_listenerInstance);
    }

}
