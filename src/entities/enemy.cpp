#include "enemy.hpp"
#include "../constants.hpp"
#include "bullet.hpp"
#include <raymath.h>

Enemy Enemy::create(Vector2 pos) {
   return Enemy(M{
       .pho = PhysicalObject::create(pos, {0, 0}),
       .health = Health::create(MAX_HEALTH),
       .shooter = Shooter::create(FIRING_COOLDOWN),
       .fear = Fear::create(),
   });
}

void Enemy::tick(Player &p) {
   Vector2 nearestPlayerPos = p.getPos();
   float playerDist = Vector2DistanceSqr(p.getPos(), getPos());
   for (float dx = -WORLD_X; dx <= WORLD_X + 1; dx += WORLD_X) {
      for (float dy = -WORLD_Y; dy <= WORLD_Y + 1; dy += WORLD_Y) {
         Vector2 newPos = p.getPos() + Vector2{dx, dy};
         float dist = Vector2DistanceSqr(getPos(), newPos);
         if (dist < playerDist) {
            playerDist = dist;
            nearestPlayerPos = newPos;
         }
      }
   }
   Vector2 dangerPos = nearestPlayerPos;
   float dangerDist = playerDist;
   for (auto &b : Bullet::getBullets()) {
      for (float dx = -WORLD_X; dx <= WORLD_X + 1; dx += WORLD_X) {
         for (float dy = -WORLD_Y; dy <= WORLD_Y + 1; dy += WORLD_Y) {
            Vector2 newPos = b.getPos() + Vector2{dx, dy};
            float dist = Vector2DistanceSqr(getPos(), newPos);
            if (dist < dangerDist) {
               dangerDist = dist;
               dangerPos = newPos;
            }
         }
      }
   }
   m.health.tick();
   m.shooter.tick();
   m.fear.tick(sqrt(dangerDist), m.shooter.cooldown(), m.health, p.getHealth());

   Vector2 accel = {0, 0};
   accel +=
       Vector2Normalize(p.getPos() - getPos()) * (MAX_FEAR - m.fear.getFear());
   accel += Vector2Normalize(getPos() - dangerPos) * m.fear.getFear();
   accel = Vector2Normalize(accel) * ACCEL;

   m.pho.tick(accel);

   if (m.shooter.cooldown() > 0)
      return;

   m.shooter.resetCooldown();
   Bullet::shoot(getPos(), Vector2Normalize(p.getPos() - getPos()));
}

Vector2 Enemy::getPos() const { return m.pho.getPos(); }

void Enemy::dealDamage(float damage) { m.health.dealDamage(damage); }

Health Enemy::getHealth() const { return m.health; }

void Enemy::draw() const { DrawCircleV(getPos(), BALL_RADIUS, RED); }

void Enemy::drawUI() const {
   DrawRectangleLinesEx({WORLD_X - 310, 10, 300, 40}, 2, RED);
   DrawRectangle(WORLD_X - 305, 15,
                 m.health.getHealth() / (float)m.health.getMaxHealth() * 290,
                 30, PINK);
}
