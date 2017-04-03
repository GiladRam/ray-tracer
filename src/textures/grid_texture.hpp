#pragma once

#include <vector>
#include "../libraries/color.hpp"
#include "texture.hpp"

class GridTexture : public Texture {
private:
  float size;
  std::vector<Color> colors;

public:
  GridTexture(float size, const std::vector<Color> &colors, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
    this->size = size;
    this->colors = colors;
  }

  Color get_color(float x, float y) const {
    auto a = (x < 0) ^ (((static_cast<int>(x / size)) & 1) == 0);
    auto b = (y < 0) ^ (((static_cast<int>(y / size)) & 1) == 0);
    return (a ^ b) ? colors[0] : colors[1];
  }
};