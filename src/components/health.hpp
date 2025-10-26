#pragma once

#include "constants.hpp"

struct Health {
    f32 m_points;
    f32 m_maxPoints;

    static Health create(f32 maxHealth);
    void damage(f32 damage);
    f32 percentage() const;
    void tick();
};
