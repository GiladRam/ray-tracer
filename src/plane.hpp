#pragma once

#include <cmath>
#include "vector.hpp"
#include "object.hpp"
#include "utility.hpp"
#include "ray.hpp"

class Plane : public Object {
public:
  Vector point, normal;

  Plane(const Vector &point, const Vector &normal, const Material &material) : Object(material) {
    this->point = point;
    this->normal = normal.normalize();
  }

  float intersect(const Ray &ray) const {
    float denominator = normal.dot(ray.direction);
    if (fabsf(denominator) < numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    float distance = (point - ray.source).dot(normal) / denominator;
    if (distance > -numeric_eps) {
      return distance;
    } else {
      return std::numeric_limits<float>::max();
    }
  }

  Vector get_normal(const Vector &position) const {
    return normal;
  }
};