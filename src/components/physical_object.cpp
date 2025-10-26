#include "physical_object.hpp"
#include "constants.hpp"
#include <raymath.h>

PhysicalObject PhysicalObject::create(Vector2 pos, Vector2 velocity) {
    return {.m_pos = pos, .m_vel = velocity};
}

void PhysicalObject::tick(Vector2 accel) {
    m_vel += accel;
    m_vel *= FRICTION;
    m_pos += m_vel;
    m_pos.x = Wrap(m_pos.x, 0, WORLD_X);
    m_pos.y = Wrap(m_pos.y, 0, WORLD_Y);
}
