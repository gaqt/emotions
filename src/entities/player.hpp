#pragma once

#include "../components/health.hpp"
#include "../components/physical_object.hpp"
#include "../components/shooter.hpp"
#include <raylib.h>

class Player {
   struct M {
      PhysicalObject pho;
      Health health;
      Shooter shooter;
   } m;
   explicit Player(M m) : m(std::move(m)) {};

 public:
   static Player create(Vector2 pos);
   void tick();
   Vector2 getPos() const;
   void dealDamage(float damage);
   Health getHealth() const;
   void draw() const;
   void drawUI() const;
};
