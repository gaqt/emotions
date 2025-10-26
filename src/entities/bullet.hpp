#pragma once

#include "../components/age.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <vector>

class Bullet {
   struct M {
      Vector2 pos;
      Vector2 velocity;
      Age age;
   } m;
   explicit Bullet(M m) : m(std::move(m)) {};

   bool tick(Player &p, Enemy &e);
   void draw() const;

 public:
   static void shoot(Vector2 source, Vector2 direction);
   static void tickAll(Player &p, Enemy &e);
   static void drawAll();
   static void clearBullets();
   static const std::vector<Bullet> &getBullets();
   Vector2 getPos() const;
   Vector2 getVelocity() const;
};
