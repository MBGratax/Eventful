#pragma once

#include <box2d/box2d.h>


namespace physics {
    class listner : public b2ContactListener {

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    };
}
