#pragma once

#include <cmath>
#include "../libraries/vector.hpp"
#include "object.hpp"
#include "../libraries/utility.hpp"
#include "../libraries/ray.hpp"

class Plane : public Object {
private:
  Vector normal;

public:
  Vector center;
  std::vector<Vector> axes;

  Plane(const Vector &center, const std::vector<Vector> &axes, const Texture *texture) : Object(texture) {
    this->center = center;
    this->axes = {axes[0].normalize(), axes[1].normalize()};
    this->normal = axes[0].det(axes[1]).normalize();
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
    auto x = difference.dot(axes[0]);
    auto y = difference.dot(axes[1]);
    return texture->get_color(x, y);
  }
};