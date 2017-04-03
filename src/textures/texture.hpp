#pragma once

#include "../libraries/color.hpp"

class Texture {
public:
  float k_diffusive;
  float k_diffusive_reflective;
  float k_specular;
  float k_reflective;
  float k_refractive;
  float k_refractive_index;

  Texture(float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) {
    this->k_diffusive = k_diffusive;
    this->k_diffusive_reflective = k_diffusive_reflective;
    this->k_specular = k_specular;
    this->k_reflective = k_reflective;
    this->k_refractive = k_refractive;
    this->k_refractive_index = k_refractive_index;
  }

  virtual Color get_color(float x, float y) const = 0;
};