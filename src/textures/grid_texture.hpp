#pragma once

#include <vector>
#include "../libraries/color.hpp"
#include "texture.hpp"

class GridTexture : public Texture {
private:
  std::vector<Color> colors;
  float scale;

public:
  GridTexture(const std::vector<Color> &colors, float scale, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
    this->colors = colors;
    this->scale = scale;
  }

  Color get_color(float x, float y) const {
    auto a = modulo(x * scale) < 0.5;
    auto b = modulo(y * scale) < 0.5;
    return (a ^ b) ? colors[0] : colors[1];
  }
};