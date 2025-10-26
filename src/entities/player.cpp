#include "player.hpp"
#include "../constants.hpp"
#include "bullet.hpp"
#include <raymath.h>

Player Player::create(Vector2 pos) {
   return {
       .m_pho = PhysicalObject::create(pos, {0, 0}),
       .m_health = Health::create(MAX_HEALTH),
       .m_shootCooldown = Timer::create(0, FIRING_COOLDOWN),
   };
}

void Player::tick() {
   m_health.tick();

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

   m_pho.tick(accel);

   m_shootCooldown.tick();
   if (!m_shootCooldown.done())
      return;

   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 direction = Vector2Normalize(GetMousePosition() - m_pho.m_pos);
      Bullet::shoot(m_pho.m_pos, direction);
      m_shootCooldown.reset();
   }
}

void Player::draw() const { DrawCircleV(m_pho.m_pos, BALL_RADIUS, BLUE); }

void Player::drawUI() const {
   DrawRectangleLinesEx({10, WORLD_Y - 50, 300, 40}, 2, WHITE);
   DrawRectangle(15, WORLD_Y - 45,
                 m_health.percentage() * 290, 30,
                 GREEN);
   DrawCircleSector(GetMousePosition() + Vector2{20, 20}, 15, 0,
                    360.0 * (1.0f - m_shootCooldown.percentage()), 10, GRAY);
}
