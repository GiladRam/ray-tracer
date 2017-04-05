#pragma once

#include <cmath>
#include "../libraries/vector.hpp"
#include "object.hpp"
#include "../libraries/utility.hpp"
#include "../libraries/ray.hpp"

class Plane : public Object {
private:
  Vector center;
  std::vector<Vector> axes;

public:
  Plane(const Vector &center, const std::vector<Vector> &axes, const Texture *texture) : Object(texture) {
    this->center = center;
    this->axes.emplace_back(axes[0].normalize());
    this->axes.emplace_back(axes[1].normalize());
    this->axes.emplace_back(axes[0].det(axes[1]).normalize());
  }

  Intersection intersect(const Ray &ray) const {
    auto denominator = axes[2].dot(ray.direction);
    if (fabsf(denominator) < numeric_eps) {
      return Intersection::MISS;
    }
    auto distance = (center - ray.source).dot(axes[2]) / denominator;
    if (distance > -numeric_eps) {
      return {.distance = distance};
    } else {
      return Intersection::MISS;
    }
  }

  Vector get_normal(const Ray &ray, const Intersection &intersection) const {
    return axes[2];
  }

  Color get_color(const Vector &position) const {
    auto difference = position - center;
    auto x = difference.dot(axes[0]);
    auto y = difference.dot(axes[1]);
    return texture->get_color(x, y);
  }
};