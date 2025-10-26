#pragma once

#include "age.hpp"
#include <utility>

class Shooter {
   struct M {
      Age cooldown;
   } m;
   explicit Shooter(M m) : m(std::move(m)) {}

 public:
   static Shooter create(int cooldown);
   void tick();
   int cooldown() const;
   int maxAge() const;
   void resetCooldown();
};
