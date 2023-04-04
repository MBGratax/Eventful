#include "Listner.h"
#include <iostream>

namespace Ventgame::Physics {
    void Listner::BeginContact(b2Contact *contact) {

        auto l_bodyA = contact->GetFixtureA()->GetBody();
        auto l_bodyB = contact->GetFixtureB()->GetBody();

        std::cout << "Begin Contact " << l_bodyA << " and " << l_bodyB << std::endl;
    }

    void Listner::EndContact(b2Contact *contact) {

        std::cout << "End Contact" << std::endl;
    }

    void Listner::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {

        b2Body *l_bodyA = contact->GetFixtureA()->GetBody();
        b2Body *l_bodyB = contact->GetFixtureB()->GetBody();

        l_bodyA->ApplyLinearImpulse(b2Vec2(-0.001f, -0.001f), l_bodyA->GetWorldCenter(), true);
        l_bodyB->ApplyLinearImpulse(b2Vec2(-0.001f, -0.001f), l_bodyB->GetWorldCenter(), true);

        std::cout << "Post Solve" << std::endl;
    }

    void Listner::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {

        std::cout << "Pre Solve" << std::endl;
    }
}