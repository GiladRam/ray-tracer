#pragma once

#include <cmath>
#include "object.hpp"
#include "../libraries/ray.hpp"

class Sphere : public Object {
public:
  Vector center;
  float radius;

  Sphere(const Vector &center, float radius, const Texture *texture) : Object(texture) {
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

  Vector get_normal(const Vector &position, const Ray &ray) const {
    return (position - center).normalize();
  }

  Color get_color(const Vector &position) const {
    auto normal = (position - center).normalize();
    auto x = (1 + atan2f(normal.z, normal.x) / static_cast<float>(M_PI)) * .5f;
    auto y = acosf(normal.y) / static_cast<float>(M_PI);
    return texture->get_color(x, y);
  }
};