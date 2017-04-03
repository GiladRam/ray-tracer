#pragma once

#include "object.hpp"
#include "../libraries/ray.hpp"

class Triangle : public Object {
friend class PolygonMesh;

private:
  Vector normal;

public:
  Vector pointA, pointB, pointC;

  Triangle(const Vector &pointA, const Vector &pointB, const Vector &pointC, const Material &material) : Object(material) {
    this->pointA = pointA;
    this->pointB = pointB;
    this->pointC = pointC;
    this->normal = (pointB - pointA).det(pointC - pointA).normalize();
  }

  float intersect(const Ray &ray) const {
    auto vectorP = ray.direction.det(pointC - pointA);
    auto det = vectorP.dot(pointB - pointA);
    if (fabsf(det) < numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto vectorT = ray.source - pointA;
    auto u = vectorT.dot(vectorP) / det;
    if (u < -numeric_eps || u > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto vectorQ = vectorT.det(pointB - pointA);
    auto v = ray.direction.dot(vectorQ) / det;
    if (v < -numeric_eps || u + v > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    auto distance = vectorQ.dot(pointC - pointA) / det;
    if (distance < -numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    return distance;
  }

  Vector get_normal(const Vector &position, const Ray &ray) const {
    return normal;
  }
};