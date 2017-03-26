#pragma once

#include <cmath>
#include "light.hpp"

class PointLight : public Light {
public:
  Vector position;

  PointLight(const Color &color, float intensity, const Vector &position) : Light(color, intensity) {
    this->position = position;
  }

  IlluminateResult illuminate(const Vector &position, const std::vector<const Object*> &objects) const {
    auto direction = position - this->position;
    auto ray = Ray(position, -direction);
    auto distance = direction.length();
    if (ray.intersect(objects) <= distance) {
      return {.direction = Vector::ZERO, .intensity = Color::ZERO};
    }
    auto intensity = this->color * this->intensity / (4 * M_PI * distance * distance);
    return {.direction = direction.normalize(), .intensity = intensity};
  }
};