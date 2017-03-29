#pragma once

#include "../color.hpp"
#include "../ray.hpp"

class Light {
public:
  Color color;
  float intensity;

  Light(const Color &color, float intensity) {
    this->color = color;
    this->intensity = intensity;
  }

  virtual float intersect(const Ray &ray) const {
    return std::numeric_limits<float>::max();
  };

  struct IlluminateResult {
    Vector direction;
    Color intensity;
  };

  virtual IlluminateResult illuminate(const Vector &position, const std::vector<const Object*> &objects) const = 0;
};