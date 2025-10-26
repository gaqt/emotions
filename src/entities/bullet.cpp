#include "bullet.hpp"
#include "../constants.hpp"
#include "blast_effect.hpp"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
using namespace std;

vector<Bullet> g_bullets;

void Bullet::shoot(Vector2 source, Vector2 direction) {
    Bullet b = {.m_pos = source + direction * (1.2 * BALL_RADIUS),
                .m_vel = direction * BULLET_SPEED,
                .m_age = Timer::create(0, BULLET_MAXAGE)};
    g_bullets.push_back(b);
}

bool Bullet::tick(usize bulletID, Player &p, Enemy &e) {
    m_pos += m_vel;
    m_pos.x = Wrap(m_pos.x, 0, WORLD_X);
    m_pos.y = Wrap(m_pos.y, 0, WORLD_Y);

    if (m_age.tick()) return true;

    if (CheckCollisionCircles(p.m_pho.m_pos,
                              BALL_RADIUS,
                              m_pos,
                              BULLET_RADIUS)) {

        p.m_health.damage(BULLET_DAMAGE);
        BlastEffect::create(m_pos);
        return true;
    } else if (CheckCollisionCircles(e.m_pho.m_pos,
                                     BALL_RADIUS,
                                     m_pos,
                                     BULLET_RADIUS)) {

        e.m_health.damage(BULLET_DAMAGE);
        BlastEffect::create(m_pos);
        return true;
    }

    // NOTE: this makes tickAll O(N^2) for N = # of bullets
    bool found = false;
    for (usize i = bulletID + 1; i < g_bullets.size(); i++) {
        if (CheckCollisionCircles(m_pos,
                                  BULLET_RADIUS,
                                  g_bullets[i].m_pos,
                                  BULLET_RADIUS)) {

            BlastEffect::create(m_pos);
            swap(g_bullets[i], g_bullets.back());
            g_bullets.pop_back();
            i--;
            found = true;
        }
    }

    return found;
}

void Bullet::tickAll(Player &p, Enemy &e) {
    for (usize i = 0; i < g_bullets.size(); i++) {
        if (g_bullets[i].tick(i, p, e)) {
            swap(g_bullets[i], g_bullets.back());
            g_bullets.pop_back();
            i--;
        }
    }
}

void Bullet::draw() const {
    DrawCircleV(PADDING_V + m_pos, BULLET_RADIUS, PURPLE);
}

void Bullet::drawAll() {
    for (Bullet &b : g_bullets) b.draw();
}

void Bullet::clearBullets() {
    g_bullets.clear();
}

const vector<Bullet> &Bullet::getBullets() {
    return g_bullets;
}
