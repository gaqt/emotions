#pragma once

#include "components/timer.hpp"
#include <raylib.h>

struct BlastEffect {
   Vector2 m_pos;
   Timer m_age;

   bool tick();
   void draw() const;

   static void create(Vector2 pos);
   static void clearEffects();
   static void tickAll();
   static void drawAll();
};
