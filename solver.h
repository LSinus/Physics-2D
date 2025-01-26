//
// Created by Leonardo Sinibaldi on 26/01/25.
//

#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "physicsObject.h"
#include "vec2.h"

class Solver{

public:
   Solver() : m_objects(){};
   void bindWorld(std::vector<PhysicsObject*>* obj) {
      m_objects = obj;
   };

   void update(float dt);

private:
   void applyGravity();
   void updatePositions(float dt);
   void applyConstraints();
   void solveCollisions();
   std::vector<PhysicsObject*>* m_objects;
   Vec2 gravity = {0.0f, 1000.0f};
};

#endif //SOLVER_H
