//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>

#include "physicsObject.h"
#include "solver.h"

class PhysicsWorld {
public:
    PhysicsWorld(Solver& solver) : m_solver(solver) { // <-- Usa una reference
        m_solver.bindWorld(&objects);
    };
    void addObject(PhysicsObject* object) {
        objects.push_back(object);
    };
    void update(float dt) {
        m_solver.update(dt);
    };

    std::vector<PhysicsObject*> objects;
private:
    Solver m_solver;
};
#endif //PHYSICSWORLD_H
