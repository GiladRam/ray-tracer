#pragma once

#include "../libraries/color.hpp"
#include "texture.hpp"

class HomoTexture : public Texture {
private:
  Color color;

public:
  HomoTexture(const Color &color, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
    this->color = color;
  }

  Color get_color(float x, float y) const {
    return color;
  }
};