#pragma once

#include "../components/health.hpp"
#include "../components/physical_object.hpp"
#include "components/timer.hpp"
#include <raylib.h>

struct Player {
   PhysicalObject m_pho;
   Health m_health;
   Timer m_shootCooldown;

   static Player create(Vector2 pos);
   void tick();
   void draw() const;
   void drawUI() const;
};
