//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#include "physicsWorld.h"

void PhysicsWorld::updatePositions(float dt) {

        for (auto& obj : objects) {
            obj->update(dt);
            energy += obj->getKineticEnergy();
            energy += obj->getPotentialEnergy();
        }

}

void PhysicsWorld::applyGravity() {
        for (auto& obj : objects) {
            obj->accelerate(gravity);
        }
}

void PhysicsWorld::applyConstraints() {
    const Vec2 position{400.f, 350.f};   // Centro del vincolo
    const float radius = 300.0f;         // Raggio del vincolo

    for (auto& obj : objects) {

            const float margin = obj->getRadius();
            // Direzione dal centro al corpo
            const Vec2 to_obj = obj->getPosition() - position;
            const float dist = to_obj.length();

            // Se il corpo è fuori dal vincolo (raggio - margin)
            if (dist > radius - margin) {
                const Vec2 n = to_obj.normalized(); // Versore normale
                const Vec2 target_pos = position + n * (radius - margin);

                obj->setPosition(target_pos);
            }
        }
}

void PhysicsWorld::solveCollisions() {
    const size_t numObjects = objects.size();

    for (int i = 0; i < numObjects; i++) {
        auto& obj1 = objects.at(i);

        // Parte da i+1 per evitare coppie duplicate
        for (int j = i + 1; j < numObjects; j++) {
            auto& obj2 = objects.at(j);

            const Vec2 collision_axis = obj1->getPosition() - obj2->getPosition();
            const float dist = collision_axis.length();

            // Distanza minima per collisione (somma dei raggi)
            const float min_dist = obj1->getRadius() + obj2->getRadius();

            if (dist < min_dist && dist > 0.0f) {  // Evita divisione per zero
                const Vec2 n = collision_axis / dist;  // Normalizzazione esplicita
                const float overlap = min_dist - dist;

                // Correzione della posizione (50% per ogni oggetto)
                const Vec2 correction = n * overlap * 0.5f;

                obj1->move(correction);
                obj2->move(-correction);
            }
        }
    }

}



void PhysicsWorld::update(float dt) {
    energy = 0.0f;
    applyGravity();
    updatePositions(dt);
    applyConstraints();

    for (int i = 0; i < 8; i++) {
        for (auto& link : links) {
            link->solve();
        }
        solveCollisions();
    }
}