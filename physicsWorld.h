//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include "physicsObject.h"
#include <vector>
#include "Link.h"

class PhysicsWorld {
public:
    void addObject(std::shared_ptr<PhysicsObject> object) {
        objects.push_back(std::move(object));
    }


    void addLink(std::shared_ptr<PhysicsObject> obj1, std::shared_ptr<PhysicsObject> obj2) {
        links.push_back(std::make_unique<Link>(obj1, obj2));
    }


    void update(float dt);

    const std::vector<std::shared_ptr<PhysicsObject>>& getObjects() const {
        return objects;
    }

    float getTotalEnergy() { return energy; }

private:
    void applyGravity();
    void updatePositions(float dt);
    void applyConstraints();
    void solveCollisions();

    std::vector<std::shared_ptr<PhysicsObject>> objects;
    std::vector<std::unique_ptr<Link>> links;
    float energy = 0;
    Vec2 gravity = {0.0f, 1000.0f};
};
#endif //PHYSICSWORLD_H
