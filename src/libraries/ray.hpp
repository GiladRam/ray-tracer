#pragma once

#include <vector>
#include "vector.hpp"
#include "../objects/object.hpp"

class Ray {
public:
  Vector source, direction;

  Ray(const Vector &source, const Vector &direction) {
    this->source = source;
    this->direction = direction.normalize();
  }

  float intersect(const std::vector<const Object*> &objects) const {
    auto intersection = Intersection::MISS;
    for (auto &object : objects) {
      auto result = object->intersect(*this);
      if (result < intersection) {
        intersection = result;
      }
    }
    return intersection.distance;
  }
};