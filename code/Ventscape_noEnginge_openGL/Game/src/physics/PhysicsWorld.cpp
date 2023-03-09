
#include "PhysicsWorld.h"
namespace Ventgame::physics{

    b2Body *PhysicsWorld::CreateBody(const b2BodyDef& bodyDef) {
        return b2->CreateBody(&bodyDef);
    }

    PhysicsWorld *PhysicsWorld::GetInstance() {
        if (instance == nullptr){
            instance = new PhysicsWorld();
        }
        return instance;
    }

    PhysicsWorld::PhysicsWorld() {
        b2 = std::make_unique<b2World>(gravity);
        b2->SetContactListener(&listenerInstance);
    }

}
