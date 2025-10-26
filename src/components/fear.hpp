#pragma once

#include "components/timer.hpp"
#include "constants.hpp"
#include "health.hpp"

struct Fear {
   f32 m_points;

   static Fear create();
   void tick(f32 dangerDist, Timer firingCooldown, Health health,
             Health playerHealth);
};
