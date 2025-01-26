//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#include "solver.h"

#include <__filesystem/recursive_directory_iterator.h>

void Solver::updatePositions(float dt) {
    if (m_objects) {
        for (auto obj_ptr : *m_objects) {
            if (obj_ptr) {
                obj_ptr->step(dt);
            }
        }
    }
}

void Solver::applyGravity() {
    if (m_objects) {
        for (auto obj_ptr : *m_objects) {
            if (obj_ptr) {
                obj_ptr->accelerate(gravity);
            }
        }
    }
}

void Solver::applyConstraints() {
    const Vec2 position{400.f, 350.f};   // Centro del vincolo
    const float radius = 300.0f;         // Raggio del vincolo
           // Margine dal bordo

    if (m_objects) {
        for (auto obj_ptr : *m_objects) {
            if (obj_ptr) {
                const float margin = obj_ptr->radius;
                // Direzione dal centro al corpo
                const Vec2 to_obj = obj_ptr->position_current - position;
                const float dist = to_obj.Length();

                // Se il corpo è fuori dal vincolo (raggio - margin)
                if (dist > radius - margin) {
                    const Vec2 n = to_obj.Normalized(); // Versore normale
                    const Vec2 target_pos = position + n * (radius - margin);

                    obj_ptr->position_current = target_pos;

                }
            }
        }
    }
}

void Solver::solveCollisions() {
    const int numObjects = m_objects->size();

    for (int h = 0; h < 10; h++) {
        for (int i = 0; i < numObjects; i++) {
            auto& obj1 = *m_objects->at(i);

            // Parte da i+1 per evitare coppie duplicate
            for (int j = i + 1; j < numObjects; j++) {
                auto& obj2 = *m_objects->at(j);

                const Vec2 collision_axis = obj1.position_current - obj2.position_current;
                const float dist = collision_axis.Length();

                // Distanza minima per collisione (somma dei raggi)
                const float min_dist = obj1.radius + obj2.radius;

                if (dist < min_dist && dist > 0.0f) {  // Evita divisione per zero
                    const Vec2 n = collision_axis / dist;  // Normalizzazione esplicita
                    const float overlap = min_dist - dist;

                    // Correzione della posizione (50% per ogni oggetto)
                    const Vec2 correction = n * overlap * 0.5f;

                    obj1.position_current += correction;
                    obj2.position_current -= correction;
                }
            }
        }
    }
}



void Solver::update(float dt) {
    applyGravity();
    updatePositions(dt);
    applyConstraints();
    solveCollisions();
}