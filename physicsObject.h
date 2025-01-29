//
// Created by Leonardo Sinibaldi on 26/01/25.
//
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "vec2.h"

class PhysicsObject {
public:

    PhysicsObject(const float radius, const float x, const float y, const bool isStatic = false) : isStatic(isStatic), radius(radius) {
        currentPosition = Vec2(x, y);
        oldPosition = currentPosition;
        acceleration = Vec2(0, 0);
    }

    void update(const float dt) {
        if (isStatic) return;
        const Vec2 velocity = currentPosition - oldPosition;
        oldPosition = currentPosition;
        currentPosition = currentPosition + velocity + acceleration * dt * dt;
        acceleration = {};

        float v = velocity.length()/dt;

        kineticEnergy = 0.5f * v * v;
    }

    void accelerate(const Vec2& acc) {
        if (isStatic) return;
        acceleration += acc;

        potentialEnergy = (-acceleration).length() * currentPosition.y;
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

    float getPotentialEnergy() const { return potentialEnergy; }
    float getKineticEnergy() const { return kineticEnergy; }


private:
    float kineticEnergy = 0;
    float potentialEnergy = 0;
    Vec2 currentPosition;
    Vec2 oldPosition;
    Vec2 acceleration;
    bool isStatic;
    float radius;
};


#endif //PHYSICSOBJECT_H
