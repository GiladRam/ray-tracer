#pragma once

#include <cmath>
#include "object.hpp"
#include "../libraries/ray.hpp"

class Sphere : public Object {
private:
  Vector center;
  float radius;
  std::vector<Vector> axes;

public:
  Sphere(const Vector &center, float radius, const std::vector<Vector> &axes, const Texture *texture) : Object(texture) {
    this->center = center;
    this->radius = radius;
    this->axes.emplace_back(axes[0].normalize());
    this->axes.emplace_back(axes[1].normalize());
    this->axes.emplace_back(axes[0].det(axes[1]).normalize());
  }

  Intersection intersect(const Ray &ray) const {
    auto v = center - ray.source;
    auto tca = v.dot(ray.direction);
    if (tca < -numeric_eps) {
      return Intersection::MISS;
    }
    auto d2 = radius * radius - v.dot(v) + tca * tca;
    if (d2 < -numeric_eps) {
      return Intersection::MISS;
    }
    auto thc = sqrtf(d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;
    if (t0 > numeric_eps) {
      return {.distance = t0};
    } else {
      return {.distance = t1};
    }
  }

  Vector get_normal(const Ray &ray, const Intersection &intersection) const {
    return (intersection.position - center).normalize();
  }

  Color get_color(const Vector &position) const {
    auto normal = (position - center).normalize();
    auto a = normal.dot(axes[0]);
    auto b = normal.dot(axes[1]);
    auto c = normal.dot(axes[2]);
    auto x = acosf(c) / numeric_pi;
    auto y = (1 + atan2f(a, b) / numeric_pi) * .5f;
    return texture->get_color(x, y);
  }
};