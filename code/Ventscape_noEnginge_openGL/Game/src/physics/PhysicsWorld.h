#pragma once
#include <box2d/box2d.h>
#include <memory>
#include "listner.h"

namespace Ventgame::physics {
    class PhysicsWorld {
    public:

        PhysicsWorld(PhysicsWorld &other) = delete;

        void operator=(const PhysicsWorld &) = delete;

        static PhysicsWorld *GetInstance();

        b2Body* CreateBody(const b2BodyDef& bodyDef);

        inline void Step(){b2->Step(timeStep, velocityIterations, positionIterations);}

    protected:

        PhysicsWorld();

    private:

        inline static PhysicsWorld *instance = nullptr;
        std::unique_ptr<b2World> b2;
        b2Vec2 gravity {0.0f, 0.0f};
        listner listenerInstance;
        int32_t velocityIterations = 10;
        int32_t positionIterations = 8;
        float timeStep = 1.0f/60.0f;

    };
}