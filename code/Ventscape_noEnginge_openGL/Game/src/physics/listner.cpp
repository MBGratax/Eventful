#include "listner.h"
#include <iostream>

namespace Ventgame::physics{
    void listner::BeginContact(b2Contact *contact) {

        auto bodyA = contact->GetFixtureA()->GetBody();
        auto bodyB = contact->GetFixtureB()->GetBody();

        std::cout << "Begin Contact " << bodyA << " and "<< bodyB << std::endl;
    }

    void listner::EndContact(b2Contact *contact) {

        std::cout << "End Contact" << std::endl;
    }

    void listner::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {

        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        b2Body *bodyB = contact->GetFixtureB()->GetBody();

       bodyA->ApplyLinearImpulse(b2Vec2(-0.001f, -0.001f), bodyA->GetWorldCenter(), true);
       bodyB->ApplyLinearImpulse(b2Vec2(-0.001f, -0.001f), bodyB->GetWorldCenter(), true);

       std::cout << "Post Solve" << std::endl;
    }

    void listner::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {

        std::cout << "Pre Solve" << std::endl;
    }
}