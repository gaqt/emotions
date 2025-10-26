#pragma once

#include <raylib.h>

struct PhysicalObject {
    Vector2 m_pos;
    Vector2 m_vel;

    static PhysicalObject create(Vector2 pos, Vector2 velocity);
    void tick(Vector2 accel);
};
