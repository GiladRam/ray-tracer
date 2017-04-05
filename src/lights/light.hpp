#pragma once

#include "../libraries/color.hpp"
#include "../libraries/ray.hpp"
#include "../libraries/illumination.hpp"

class Light {
public:
  Color color;
  float intensity;

  Light(const Color &color, float intensity) {
    this->color = color;
    this->intensity = intensity;
  }

  virtual ~Light() {}

  virtual float intersect(const Ray &ray) const = 0;

  virtual Illumination illuminate(const Vector &position, const std::vector<const Object*> &objects) const = 0;
};