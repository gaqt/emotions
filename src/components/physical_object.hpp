#pragma once

#include <raylib.h>
#include <utility>

class PhysicalObject {
   struct M {
      Vector2 pos;
      Vector2 velocity;
   } m;
   explicit PhysicalObject(M m) : m(std::move(m)) {};

 public:
   static PhysicalObject create(Vector2 pos, Vector2 velocity);
   void tick(Vector2 accel);
   Vector2 getPos() const;
   Vector2 getVelocity() const;
};
