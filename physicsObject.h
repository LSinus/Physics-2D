//
// Created by Leonardo Sinibaldi on 26/01/25.
//
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "vec2.h"

class PhysicsObject {
public:

    PhysicsObject(float radius, float x, float y, bool isStatic = false) : radius(radius) {
        currentPosition = Vec2(x, y);
        oldPosition = currentPosition;
        acceleration = Vec2(0, 0);
    }

    void update(const float dt) {
        const Vec2 velocity = currentPosition - oldPosition;
        oldPosition = currentPosition;
        currentPosition = currentPosition + velocity + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate(const Vec2& acc) {
        acceleration += acc;
    }

    const Vec2& getPosition() const { return currentPosition; }
    float getRadius() const { return radius; }

    void setPosition(const Vec2& newPosition) {
        if (!isStatic) {
            currentPosition = newPosition;
        }
    }

    void move(const Vec2& delta) {
        if (!isStatic) {
            currentPosition = currentPosition + delta;
        }
    }


private:
    Vec2 currentPosition;
    Vec2 oldPosition;
    Vec2 acceleration;
    bool isStatic;
    float radius;
};


#endif //PHYSICSOBJECT_H
