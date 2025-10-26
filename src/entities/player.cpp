#include "player.hpp"
#include "../constants.hpp"
#include "bullet.hpp"
#include <raymath.h>

Player Player::create(Vector2 pos) {
   return Player(M{
       .pho = PhysicalObject::create(pos, {0, 0}),
       .health = Health::create(MAX_HEALTH),
       .shooter = Shooter::create(FIRING_COOLDOWN),
   });
}

void Player::tick() {
   m.health.tick();

   Vector2 accel = {0, 0};
   if (IsKeyDown(KEY_W)) {
      accel.y -= 1;
   }
   if (IsKeyDown(KEY_S)) {
      accel.y += 1;
   }
   if (IsKeyDown(KEY_A)) {
      accel.x -= 1;
   }
   if (IsKeyDown(KEY_D)) {
      accel.x += 1;
   }
   accel = Vector2Normalize(accel) * ACCEL;

   m.pho.tick(accel);

   m.shooter.tick();
   if (m.shooter.cooldown() > 0)
      return;

   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 direction = Vector2Normalize(GetMousePosition() - getPos());
      Bullet::shoot(getPos(), direction);
      m.shooter.resetCooldown();
   }
}

Vector2 Player::getPos() const { return m.pho.getPos(); }

void Player::dealDamage(float damage) { m.health.dealDamage(damage); }

Health Player::getHealth() const {
   return m.health;
}

void Player::draw() const { DrawCircleV(getPos(), BALL_RADIUS, BLUE); }

void Player::drawUI() const {
   DrawRectangleLinesEx({10, WORLD_Y - 50, 300, 40}, 2, WHITE);
   DrawRectangle(15, WORLD_Y - 45,
                 m.health.getHealth() / (float)m.health.getMaxHealth() * 290,
                 30, GREEN);
   DrawCircleSector(GetMousePosition() + Vector2{20, 20}, 15, 0,
                    360.0 * m.shooter.cooldown() / m.shooter.maxAge(), 10, GRAY);
}
