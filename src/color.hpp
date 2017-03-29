#pragma once

#include "vector.hpp"

class Color : public Vector {
public:
  static const Color ZERO, BLUE, GRAY, RED, YELLOW, WHITE;

  Color(float x = 0, float y = 0, float z = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Color(const Vector &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
  }
};

const auto Color::ZERO = Color(0, 0, 0);
const auto Color::BLUE = Color(.65, .77, .97);
const auto Color::GRAY = Color(.1, .1, .1);
const auto Color::RED = Color(1, .32, .36);
const auto Color::YELLOW = Color(.9, .72, .46);
const auto Color::WHITE = Color(1, 1, 1);