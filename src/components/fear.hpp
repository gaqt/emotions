#pragma once

#include "health.hpp"
#include <raylib.h>
#include <utility>

class Fear {
   struct M {
      float fear;
   } m;
   explicit Fear(M m) : m(std::move(m)) {};

 public:
   static Fear create();
   float getFear() const;
   void tick(float dangerDist, float firingCooldown, Health health,
             Health playerHealth);
};
