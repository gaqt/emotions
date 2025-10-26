#include "age.hpp"

Age Age::create(int age, int maxAge) {
   return Age(M{.age = age, .maxAge = maxAge});
}

bool Age::tick() {
   m.age++;
   return m.age >= m.maxAge;
}

int Age::getAge() const { return m.age; }

int Age::getMaxAge() const { return m.maxAge; }

void Age::reset() { m.age = 0; }
