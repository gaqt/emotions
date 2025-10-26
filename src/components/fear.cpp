#include "fear.hpp"
#include "../constants.hpp"
#include <algorithm>
#include <raymath.h>
using namespace std;

Fear Fear::create() { return Fear(M{.fear = 0}); }

float Fear::getFear() const { return m.fear; }

void Fear::tick(float dangerDist, float firingCooldown, Health health,
                Health playerHealth) {
   float f = health.getMaxHealth() - health.getHealth();
   f += max(0.0f, 200 - dangerDist);
   f += firingCooldown;
   f += playerHealth.getHealth();
   f = Clamp(f, 0, MAX_FEAR);

   m.fear = f;
}
