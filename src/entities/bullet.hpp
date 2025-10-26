#pragma once

#include "components/timer.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <vector>

struct Bullet {
    Vector2 m_pos;
    Vector2 m_vel;
    Timer m_age;

    bool tick(Player &p, Enemy &e);
    void draw() const;

    static void shoot(Vector2 source, Vector2 direction);
    static void tickAll(Player &p, Enemy &e);
    static void drawAll();
    static void clearBullets();
    static const std::vector<Bullet> &getBullets();
};
