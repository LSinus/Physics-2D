//
// Created by Leonardo Sinibaldi on 26/01/25.
//
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "vec2.h"

class PhysicsObject {
public:

    PhysicsObject(float radius, float x, float y) : radius(radius) {
        position_current = Vec2(x, y);
        position_old = position_current;
        acceleration = Vec2(0, 0);
    }

    void step(float dt) {
        const Vec2 velocity = position_current - position_old;
        position_old = position_current;
        position_current = position_current + velocity + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate(Vec2 acc) {
        acceleration += acc;
    }



public:
    Vec2 position_current;
    Vec2 position_old;
    Vec2 acceleration;
    float radius;
};


#endif //PHYSICSOBJECT_H
