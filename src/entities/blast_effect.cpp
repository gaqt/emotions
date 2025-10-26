#include "blast_effect.hpp"
#include "../constants.hpp"
using namespace std;

std::vector<BlastEffect> effects;

void BlastEffect::create(Vector2 pos) {
   BlastEffect e =
       BlastEffect(M{.pos = pos, .age = Age::create(0, BLAST_MAXAGE)});
   effects.push_back(e);
}

void BlastEffect::clearEffects() {
   effects.clear();
}

bool BlastEffect::tick() { return m.age.tick(); }

void BlastEffect::tickAll() {
   for (size_t i = 0; i < effects.size(); i++) {
      if (effects[i].tick()) {
         swap(effects[i], effects.back());
         effects.pop_back();
         i--;
      }
   }
}

void BlastEffect::draw() const {
   DrawRing(m.pos, m.age.getAge() * BLAST_GROWTH,
            m.age.getAge() * BLAST_GROWTH + 5, 0, 360, 20, PINK);
}

void BlastEffect::drawAll() {
   for (BlastEffect &e : effects)
      e.draw();
}
