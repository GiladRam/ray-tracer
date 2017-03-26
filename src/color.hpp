#pragma once

#include "vector.hpp"

class Color : public Vector {
public:
  static const Color ZERO, BLACK, BLUE, RED, YELLOW, WHITE;

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

const Color Color::ZERO = Color(0, 0, 0);
const Color Color::BLACK = Color(0, 0, 0);
const Color Color::BLUE = Color(0.65, 0.77, 0.97);
const Color Color::RED = Color(1, 0.32, 0.36);
const Color Color::YELLOW = Color(0.9, 0.72, 0.46);
const Color Color::WHITE = Color(1, 1, 1);