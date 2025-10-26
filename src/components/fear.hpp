#pragma once

#include "components/timer.hpp"
#include "constants.hpp"
#include "entities/player.hpp"
#include "health.hpp"

struct Fear {
    f32 m_points;

    static Fear create();
    f32 percentage() const;
    void tick(f32 dangerDist,
              Timer firingCooldown,
              Health health,
              Player &player);
};
