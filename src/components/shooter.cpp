#include "shooter.hpp"
#include <algorithm>
using namespace std;

Shooter Shooter::create(int cooldown) {
   return Shooter(M{.cooldown = Age::create(0, cooldown)});
}

void Shooter::tick() { m.cooldown.tick(); }

int Shooter::cooldown() const {
   return max(0, m.cooldown.getMaxAge() - m.cooldown.getAge());
}

int Shooter::maxAge() const {
   return m.cooldown.getMaxAge();
}

void Shooter::resetCooldown() { m.cooldown.reset(); }
