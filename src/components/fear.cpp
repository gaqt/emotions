#include "fear.hpp"
#include "../constants.hpp"
#include <algorithm>
#include <raymath.h>
using namespace std;

Fear Fear::create() { return {.m_points = 0}; }

void Fear::tick(f32 dangerDist, Timer firingCooldown, Health health,
                Health playerHealth) {

   m_points = health.m_maxPoints - health.m_points;
   m_points += max(0.0f, 200 - dangerDist);
   m_points += 60.0f * firingCooldown.percentage();
   m_points += playerHealth.m_points;
   m_points = Clamp(m_points, 0, MAX_FEAR);
}
