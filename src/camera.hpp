#pragma once

#include <cmath>
#include "vector.hpp"
#include "ray.hpp"

class Camera {
private:
  Vector position;
  float angle, ratio;

public:
  int width, height, field;

  Camera(const Vector &position = Vector::ZERO, int width = 2400, int height = 1800, int field = 45) {
    this->position = position;
    this->width = width;
    this->height = height;
    this->field = field;
    this->angle = tanf(field * .5f * static_cast<float>(M_PI) / 180);
    this->ratio = static_cast<float>(width) / height;
  }

  Ray ray(int x, int y) const {
    float dx = ((2.f * x + 1) / static_cast<float>(width) - 1) * angle * ratio;
    float dy = -((2.f * y + 1) / static_cast<float>(height) - 1) * angle;
    return Ray(position, Vector(dx, dy, -1));
  }
};