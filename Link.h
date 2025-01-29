#ifndef LINK_H
#define LINK_H

#include "physicsObject.h"
#include "vec2.h"
#include <memory>

class Link {
public:
    Link(std::shared_ptr<PhysicsObject> obj1, std::shared_ptr<PhysicsObject> obj2)
        : obj1(obj1), obj2(obj2) {
        // Store the initial distance between object centers plus their radii
        Vec2 delta = obj1->getPosition() - obj2->getPosition();
        restLength = delta.length();
    }

    void solve() {
        Vec2 delta = obj1->getPosition() - obj2->getPosition();
        float currentLength = delta.length();

        if (currentLength < 0.0001f) return; // Avoid division by zero

        // Calculate the desired distance between centers
        float desiredDistance = restLength;

        // Calculate normalized direction
        Vec2 n = delta / currentLength;

        // Calculate the position correction to maintain desired distance
        Vec2 correction = n * (currentLength - desiredDistance) * 0.5f;

        obj1->move(-correction);
        obj2->move(correction);
    }

private:
    std::shared_ptr<PhysicsObject> obj1;
    std::shared_ptr<PhysicsObject> obj2;
    float restLength;  // The distance we want to maintain
};

#endif //LINK_H