//
// Created by Leonardo Sinibaldi on 05/02/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <vector>
#include "physicsObject.h"

std::shared_ptr<PhysicsObject> createObject(PhysicsWorld& world, std::vector<std::unique_ptr<sf::CircleShape>>& shapes,  float radius, float x, float y, bool isStatic = false, sf::Color color = sf::Color::White) {
    // Create physics object
    auto physicsObj = std::make_shared<PhysicsObject>(radius, x, y, isStatic);

    // Create graphics object
    auto shape = std::make_unique<sf::CircleShape>(radius);
    shape->setFillColor(color);
    shape->setOrigin({shape->getRadius(), shape->getRadius()});
    shape->setPosition({x, y});

    // Add to world and shapes vector
    world.addObject(physicsObj);
    shapes.push_back(std::move(shape));

    return physicsObj;
}

#endif //UTILS_H
