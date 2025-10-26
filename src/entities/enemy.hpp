#pragma once

#include "../components/fear.hpp"
#include "../components/health.hpp"
#include "../components/physical_object.hpp"
#include "../components/shooter.hpp"
#include "player.hpp"
#include <raylib.h>

class Enemy {
   struct M {
      PhysicalObject pho;
      Health health;
      Shooter shooter;
      Fear fear;
   } m;
   explicit Enemy(M m) : m(std::move(m)) {};

 public:
   static Enemy create(Vector2 pos);
   void tick(Player &p);
   Vector2 getPos() const;
   void dealDamage(float damage);
   Health getHealth() const;
   void draw() const;
   void drawUI() const;
};
