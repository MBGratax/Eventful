#pragma once

#include <box2d/box2d.h>

namespace Ventgame::Physics {
    class Listner : public b2ContactListener {

        void BeginContact(b2Contact *contact) override;

        void EndContact(b2Contact *contact) override;

        void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;

        void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    };
}
