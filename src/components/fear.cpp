#include "fear.hpp"
#include "../constants.hpp"
#include <algorithm>
#include <cstdio>
#include <raymath.h>
using namespace std;

Fear Fear::create() {
    return {.m_points = 0};
}

f32 Fear::percentage() const {
    return m_points / MAX_FEAR;
}

void Fear::tick(f32 dangerDist,
                Timer firingCooldown,
                Health health,
                Player &player) {

    m_points = 0;
    m_points += 200.f * (1.f - health.percentage());
    m_points += 200.f * player.m_health.percentage();
    m_points += max(.0f, 400.f - dangerDist);
    m_points += 50.f * (1.f - firingCooldown.percentage());
    m_points += 50.f * player.m_shootCooldown.percentage();
    m_points = Clamp(m_points, 0, MAX_FEAR);
}
