#pragma once

#include <utility>
class Age {
   struct M {
      int age;
      int maxAge;
   } m;
   explicit Age(M m) : m(std::move(m)) {};

 public:
   static Age create(int age, int maxAge);
   bool tick();
   int getAge() const;
   int getMaxAge() const;
   void reset();
};
