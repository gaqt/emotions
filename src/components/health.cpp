#include "health.hpp"
#include "../constants.hpp"

Health Health::create(f32 maxHealth) {
    return {
        .m_points = maxHealth,
        .m_maxPoints = maxHealth,
    };
}

void Health::damage(f32 damage) {
    m_points -= damage;
}

f32 Health::percentage() const {
    return m_points / m_maxPoints;
}

void Health::tick() {
    m_points -= HEALTH_DRAIN;
}
