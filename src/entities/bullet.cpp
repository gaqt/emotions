#include "bullet.hpp"
#include "../constants.hpp"
#include "blast_effect.hpp"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
using namespace std;

std::vector<Bullet> bullets;

void Bullet::shoot(Vector2 source, Vector2 direction) {
   Bullet b = Bullet(M{.pos = source + direction * (1.2 * BALL_RADIUS),
                       .velocity = direction * BULLET_SPEED,
                       .age = Age::create(0, BULLET_MAXAGE)});
   bullets.push_back(b);
}

bool Bullet::tick(Player &p, Enemy &e) {
   m.pos += m.velocity;
   m.pos.x = Wrap(m.pos.x, 0, WORLD_X);
   m.pos.y = Wrap(m.pos.y, 0, WORLD_Y);

   if (m.age.tick())
      return true;

   if (CheckCollisionCircles(p.getPos(), BALL_RADIUS, m.pos, BULLET_RADIUS)) {
      p.dealDamage(BULLET_DAMAGE);
      BlastEffect::create(m.pos);
      return true;
   } else if (CheckCollisionCircles(e.getPos(), BALL_RADIUS, m.pos,
                                    BULLET_RADIUS)) {
      e.dealDamage(BULLET_DAMAGE);
      BlastEffect::create(m.pos);
      return true;
   }

   return false;
}

void Bullet::tickAll(Player &p, Enemy &e) {
   for (size_t i = 0; i < bullets.size(); i++) {
      if (bullets[i].tick(p, e)) {
         swap(bullets[i], bullets.back());
         bullets.pop_back();
         i--;
      }
   }
}

void Bullet::draw() const { DrawCircleV(m.pos, BULLET_RADIUS, PURPLE); }

void Bullet::drawAll() {
   for (Bullet &b : bullets)
      b.draw();
}

void Bullet::clearBullets() { bullets.clear(); }

const vector<Bullet> &Bullet::getBullets() { return bullets; }

Vector2 Bullet::getPos() const { return m.pos; }

Vector2 Bullet::getVelocity() const { return m.velocity; }
