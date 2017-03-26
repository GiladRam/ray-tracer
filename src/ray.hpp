#pragma once

#include <vector>
#include "vector.hpp"
#include "object.hpp"

class Ray {
public:
  Vector source, direction;

  Ray(const Vector &source, const Vector &direction) {
    this->source = source;
    this->direction = direction.normalize();
  }

  float intersect(const std::vector<const Object*> &objects) const {
    float distance = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      float length = object->intersect(*this);
      if (length < distance) {
        distance = length;
      }
    }
    return distance;
  }
};