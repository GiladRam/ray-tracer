#pragma once

#include "../libraries/color.hpp"
#include "texture.hpp"
#include "../externals/stb_image.hpp"

class ImageTexture : public Texture {
private:
  unsigned char* image;
  int width, height;
  float scale;

public:
  ImageTexture(const std::string &path, float scale, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
    this->image = stbi_load(path.c_str(), &width, &height, nullptr, 3);
    this->scale = scale;
  }

  Color get_color(float x, float y) const {
    auto a = static_cast<int>(round(scale * x) - height / 2);
    auto b = static_cast<int>(round(scale * y) - width / 2);
    auto p = modulo(a, height) * width + modulo(b, width);
    return Color(image[p * 3] / 255.f, image[p * 3 + 1] / 255.f, image[p * 3 + 2] / 255.f);
  }
};