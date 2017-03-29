#pragma once

#include <cmath>
#include "object.hpp"
#include "ray.hpp"

class Sphere : public Object {
public:
  Vector center;
  float radius;

  Sphere(const Vector &center, float radius, const Material &material) : Object(material) {
    this->center = center;
    this->radius = radius;
  }

  float intersect(const Ray &ray) const {
    auto v = center - ray.source;
    float tca = v.dot(ray.direction);
    if (tca < 0) {
      return std::numeric_limits<float>::max();
    }
    float d2 = radius * radius - v.dot(v) + tca * tca;
    if (d2 < 0) {
      return std::numeric_limits<float>::max();
    }
    float thc = sqrtf(d2);
    float t0 = tca - thc;
    float t1 = tca + thc;
    if (t0 > 0) {
      return t0;
    } else {
      return t1;
    }
  }

  Vector get_normal(const Vector &position) const {
    return (position - center).normalize();
  }
};