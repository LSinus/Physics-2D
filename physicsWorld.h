//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>

#include "physicsObject.h"

class PhysicsWorld {
public:
    PhysicsWorld() {

    };
    void addObject(std::unique_ptr<PhysicsObject> object) {
        objects.push_back(std::move(object));
    }

    void update(float dt);

    const std::vector<std::unique_ptr<PhysicsObject>>& getObjects() const {
        return objects;
    }

private:
    void applyGravity();
    void updatePositions(float dt);
    void applyConstraints();
    void solveCollisions();

    std::vector<std::unique_ptr<PhysicsObject>> objects;
    Vec2 gravity = {0.0f, 1000.0f};
};
#endif //PHYSICSWORLD_H
