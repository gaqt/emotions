#pragma once

#include "constants.hpp"

struct Timer {
    i32 m_ticks;
    i32 m_maxTicks;

    static Timer create(i32 ticks, i32 maxTicks);
    bool tick();
    bool done() const;
    f32 percentage() const;
    void reset();
};
