#pragma once

#include <utility>

class Health {
   struct M {
      float health;
      float maxHealth;
   } m;
   explicit Health(M m) : m(std::move(m)) {};

   public:
   static Health create(float maxHealth);
   float getHealth() const;
   float getMaxHealth() const;
   void dealDamage(float damage);
   void tick();
};
