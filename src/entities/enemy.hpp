#pragma once

#include "../components/fear.hpp"
#include "../components/health.hpp"
#include "../components/physical_object.hpp"
#include "player.hpp"
#include <raylib.h>

struct Enemy {
    PhysicalObject m_pho;
    Health m_health;
    Timer m_shootCooldown;
    Fear m_fear;

  public:
    static Enemy create(Vector2 pos);
    void tick(Player &p);
    void draw() const;
    void drawUI() const;
};
