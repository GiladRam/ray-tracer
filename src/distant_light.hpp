#pragma once

#include "light.hpp"

class DistantLight : public Light {
public:
  Vector direction;

  DistantLight(const Color &color, float intensity, const Vector &direction) : Light(color, intensity) {
    this->direction = direction.normalize();
  }

  IlluminateResult illuminate(const Vector &position, const std::vector<const Object*> &objects) const {
    auto ray = Ray(position, -direction);
    if (ray.intersect(objects) < std::numeric_limits<float>::max()) {
      return {.direction = direction, .intensity = color * intensity};
    } else {
      return {.direction = Vector::ZERO, .intensity = Color::ZERO};
    }
  }
};