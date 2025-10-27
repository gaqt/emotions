#include "enemy.hpp"
#include "../constants.hpp"
#include "bullet.hpp"
#include <cstdio>
#include <raymath.h>

Enemy Enemy::create(Vector2 pos) {
    return {
        .m_pho = PhysicalObject::create(pos, {0, 0}),
        .m_health = Health::create(MAX_HEALTH),
        .m_shootCooldown = Timer::create(0, FIRING_COOLDOWN),
        .m_fear = Fear::create(),
    };
}

void Enemy::tick(Player &p) {

    Vector2 nearestPlayerPos = p.m_pho.m_pos;
    float playerDist = Vector2DistanceSqr(p.m_pho.m_pos, m_pho.m_pos);
    for (float dx = -WORLD_X; dx <= WORLD_X + 1; dx += WORLD_X) {
        for (float dy = -WORLD_Y; dy <= WORLD_Y + 1; dy += WORLD_Y) {
            Vector2 newPos = p.m_pho.m_pos + Vector2{dx, dy};
            float dist = Vector2DistanceSqr(m_pho.m_pos, newPos);
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
                Vector2 newPos = b.m_pos + Vector2{dx, dy};
                float dist = Vector2DistanceSqr(m_pho.m_pos, newPos);
                if (dist < dangerDist) {
                    dangerDist = dist;
                    dangerPos = newPos;
                }
            }
        }
    }

    m_health.tick();
    m_shootCooldown.tick();
    m_fear.tick(sqrt(dangerDist), m_shootCooldown, m_health, p);

    Vector2 accel = {0, 0};
    accel += Vector2Normalize(nearestPlayerPos - m_pho.m_pos)
           * (1.0 - m_fear.percentage());
    accel += Vector2Normalize(m_pho.m_pos - dangerPos) * m_fear.percentage();
    accel += Vector2Normalize({static_cast<f32>(rand() % 100) - 50,
                               static_cast<f32>(rand() % 100) - 50})
           * .05f;
    accel = Vector2Normalize(accel) * ACCEL;

    m_pho.tick(accel);

    if (!m_shootCooldown.done()) return;

    m_shootCooldown.reset();
    Vector2 shootDir = Vector2Normalize(nearestPlayerPos - m_pho.m_pos);
    shootDir = Vector2Rotate(shootDir, (rand() % 100 - 50) / 400.f);
    Bullet::shoot(m_pho.m_pos, shootDir);
}


void Enemy::draw() const {
    DrawCircleV(PADDING_V + m_pho.m_pos, BALL_RADIUS, RED);
}

void Enemy::drawUI() const {
    DrawRectangleLinesEx(PADDED_REC(WORLD_X - 310, 10, 300, 40), 2, RED);
    DrawRectangleRec(
        PADDED_REC(WORLD_X - 305, 15, m_health.percentage() * 290, 30),
        PINK);
}
