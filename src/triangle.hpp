#pragma once

#include "object.hpp"
#include "ray.hpp"

class Triangle : public Object {
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
    Vector vectorP = ray.direction.det(pointC - pointA);
    float det = vectorP.dot(pointB - pointA);
    if (fabsf(det) < numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    Vector vectorT = ray.source - pointA;
    float u = vectorT.dot(vectorP) / det;
    if (u < -numeric_eps || u > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    Vector vectorQ = vectorT.det(pointB - pointA);
    float v = ray.direction.dot(vectorQ) / det;
    if (v < -numeric_eps || u + v > 1 + numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    float distance = vectorQ.dot(pointC - pointA) / det;
    if (distance < -numeric_eps) {
      return std::numeric_limits<float>::max();
    }
    return distance;
  }

  Vector get_normal(const Vector &position) const {
    return normal;
  }
};