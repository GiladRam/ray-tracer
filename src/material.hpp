#pragma once

#include "color.hpp"

class Material {
public:
  Color color;
  float k_diffusive;
  float k_specular;
  float k_reflective;
  float k_diffusive_reflective;
  float k_refractive;
  float k_refractive_index;

  Material(
    const Color &color = Color(),
    float k_diffusive = 1,
    float k_specular = 1,
    float k_reflective = 0,
    float k_diffusive_reflective = 0,
    float k_refractive = 0,
    float k_refractive_index = 1
  ) {
    this->color = color;
    this->k_diffusive = k_diffusive;
    this->k_specular = k_specular;
    this->k_reflective = k_reflective;
    this->k_diffusive_reflective = k_diffusive_reflective;
    this->k_refractive = k_refractive;
    this->k_refractive_index = k_refractive_index;
  }
};