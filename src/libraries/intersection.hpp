#pragma once

#include <limits>

class Object;

class Intersection {
public:
  float distance;
  Vector position;
  const Object* face;

  static const Intersection MISS;

  bool operator < (const Intersection &i) {
    return distance < i.distance;
  }
};

const Intersection Intersection::MISS = {.distance = std::numeric_limits<float>::max()};