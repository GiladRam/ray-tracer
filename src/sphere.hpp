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
    auto tca = v.dot(ray.direction);
    if (tca < -numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto d2 = radius * radius - v.dot(v) + tca * tca;
    if (d2 < -numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto thc = sqrtf(d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;
    if (t0 > numeric_eps) {
      return t0;
    } else {
      return t1;
    }
  }

  Vector get_normal(const Vector &position) const {
    return (position - center).normalize();
  }
};