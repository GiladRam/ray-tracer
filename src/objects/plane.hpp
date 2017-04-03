#pragma once

#include <cmath>
#include "../libraries/vector.hpp"
#include "object.hpp"
#include "../libraries/utility.hpp"
#include "../libraries/ray.hpp"

class Plane : public Object {
public:
  Vector center, normal;

  Plane(const Vector &center, const Vector &normal, const Texture *texture) : Object(texture) {
    this->center = center;
    this->normal = normal.normalize();
  }

  float intersect(const Ray &ray) const {
    auto denominator = normal.dot(ray.direction);
    if (fabsf(denominator) < numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto distance = (center - ray.source).dot(normal) / denominator;
    if (distance > -numeric_eps) {
      return distance;
    } else {
      return std::numeric_limits<float>::max();
    }
  }

  Vector get_normal(const Vector &position, const Ray &ray) const {
    return normal;
  }

  Color get_color(const Vector &position) const {
    auto difference = position - center;
    auto x = difference.dot(Vector(1, 0, 0));
    auto y = difference.dot(Vector(0, 0, 1));
    return texture->get_color(x, y);
  }
};