#pragma once

#include <cmath>
#include "libraries/vector.hpp"
#include "libraries/ray.hpp"

class Camera {
private:
  Vector position;
  float angle, ratio;

public:
  int width, height, field;

  Camera(const Vector &position, int width, int height, int field) {
    this->position = position;
    this->width = width;
    this->height = height;
    this->field = field;
    this->angle = tanf(field * .5f * static_cast<float>(M_PI) / 180);
    this->ratio = static_cast<float>(width) / height;
  }

  Ray ray(int x, int y) const {
    auto dx = ((2.f * x + 1) / width - 1) * angle * ratio;
    auto dy = -((2.f * y + 1) / height - 1) * angle;
    return Ray(position, Vector(dx, dy, -1));
  }
};