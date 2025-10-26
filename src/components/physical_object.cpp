#include "physical_object.hpp"
#include "../constants.hpp"
#include <raymath.h>

PhysicalObject PhysicalObject::create(Vector2 pos, Vector2 velocity) {
   return PhysicalObject(M{.pos = pos, .velocity = velocity});
}

void PhysicalObject::tick(Vector2 accel) {
   m.velocity += accel;
   m.velocity *= FRICTION;
   m.pos += m.velocity;
   m.pos.x = Wrap(m.pos.x, 0, WORLD_X);
   m.pos.y = Wrap(m.pos.y, 0, WORLD_Y);
}

Vector2 PhysicalObject::getPos() const { return m.pos; }

Vector2 PhysicalObject::getVelocity() const { return m.velocity; }
