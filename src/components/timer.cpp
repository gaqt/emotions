#include "timer.hpp"
#include <algorithm>
using namespace std;

Timer Timer::create(i32 ticks, i32 maxTicks) {
    return {.m_ticks = ticks, .m_maxTicks = maxTicks};
}

bool Timer::tick() {
    m_ticks = min(m_ticks+1, m_maxTicks);
    return m_ticks >= m_maxTicks;
}

bool Timer::done() const {
    return m_ticks >= m_maxTicks;
}

f32 Timer::percentage() const {
    return (f32)m_ticks / (f32)m_maxTicks;
}

void Timer::reset() {
    m_ticks = 0;
}
