#pragma once

#include "../components/age.hpp"
#include <raylib.h>
#include <vector>

class BlastEffect {
   struct M {
      Vector2 pos;
      Age age;
   } m;
   explicit BlastEffect(M m) : m(std::move(m)) {};

   bool tick();
   void draw() const;

 public:
   static void create(Vector2 pos);
   static void clearEffects();
   static void tickAll();
   static void drawAll();
};
