#include "blast_effect.hpp"
#include "../constants.hpp"
#include <vector>
using namespace std;

vector<BlastEffect> g_effects;

void BlastEffect::create(Vector2 pos) {
    BlastEffect e = {.m_pos = pos, .m_age = Timer::create(0, BLAST_MAXAGE)};
    g_effects.push_back(e);
}

void BlastEffect::clearEffects() {
    g_effects.clear();
}

bool BlastEffect::tick() {
    return m_age.tick();
}

void BlastEffect::tickAll() {
    for (size_t i = 0; i < g_effects.size(); i++) {
        if (g_effects[i].tick()) {
            swap(g_effects[i], g_effects.back());
            g_effects.pop_back();
            i--;
        }
    }
}

void BlastEffect::draw() const {
    DrawRing(PADDED_VEC2(m_pos.x, m_pos.y),
             m_age.m_ticks * BLAST_GROWTH,
             m_age.m_ticks * BLAST_GROWTH + 5,
             0,
             360,
             20,
             PINK);
}

void BlastEffect::drawAll() {
    for (BlastEffect &e : g_effects) e.draw();
}
