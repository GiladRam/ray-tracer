#pragma once

#include "../libraries/vector.hpp"

class Color : public Vector {
public:
  static const Color ZERO, GRAY;

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
const Color Color::GRAY = Color(.1, .1, .1);