#include "health.hpp"
#include "../constants.hpp"

Health Health::create(float maxHealth) {
   return Health(M{
       .health = maxHealth,
       .maxHealth = maxHealth,
   });
}

float Health::getHealth() const { return m.health; }

float Health::getMaxHealth() const { return m.maxHealth; }

void Health::dealDamage(float damage) { m.health -= damage; }

void Health::tick() { m.health -= HEALTH_DRAIN; }
