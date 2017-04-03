#pragma once

#include "object.hpp"
#include "../libraries/ray.hpp"

class Triangle : public Object {
friend class PolygonMesh;

private:
  Vector normal;

public:
  std::vector<Vector> points;

  Triangle(const std::vector<Vector> &points, const Texture *texture) : Object(texture) {
    this->points = points;
    this->normal = (points[1] - points[0]).det(points[2] - points[0]).normalize();
  }

  float intersect(const Ray &ray) const {
    auto vectorP = ray.direction.det(points[2] - points[0]);
    auto det = vectorP.dot(points[1] - points[0]);
    if (fabsf(det) < numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto vectorT = ray.source - points[0];
    auto u = vectorT.dot(vectorP) / det;
    if (u < -numeric_eps || u > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto vectorQ = vectorT.det(points[1] - points[0]);
    auto v = ray.direction.dot(vectorQ) / det;
    if (v < -numeric_eps || u + v > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto distance = vectorQ.dot(points[2] - points[0]) / det;
    if (distance < -numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    return distance;
  }

  Vector get_normal(const Vector &position, const Ray &ray) const {
    return normal;
  }
};