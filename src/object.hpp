#pragma once

#include "material.hpp"
#include "vector.hpp"

class Ray;

class Object {
public:
  Material material;

  Object(const Material &material) {
    this->material = material;
  }

  virtual float intersect(const Ray &ray) const = 0;

  virtual Vector get_normal(const Vector &pos) const = 0;

  virtual Color get_color(const Vector &pos) const {
    return material.color;
  }
};