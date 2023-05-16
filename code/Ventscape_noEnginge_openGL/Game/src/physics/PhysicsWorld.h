#pragma once

#include <box2d/box2d.h>
#include <memory>
#include "Listner.h"

namespace Ventgame::Physics {
    class PhysicsWorld {
    public:

        PhysicsWorld(PhysicsWorld &other) = delete;

        void operator=(const PhysicsWorld &) = delete;

        static PhysicsWorld& GetInstance(){
            static PhysicsWorld _instance;
            return _instance;
        }

        b2Body *CreateBody(const b2BodyDef &bodyDef);

        inline void Step() { _b2->Step(_timeStep, _velocityIterations, _positionIterations); }

    protected:

        PhysicsWorld();

    private:
        std::unique_ptr<b2World> _b2;
        b2Vec2 _gravity{0.0f, 0.0f};
        Listner _listenerInstance;
        int32_t _velocityIterations = 10;
        int32_t _positionIterations = 8;
        float _timeStep = 1.0f / 60.0f;

    };
}