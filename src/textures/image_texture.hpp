#pragma once

#include "../libraries/color.hpp"
#include "texture.hpp"
#include "../externals/stb_image.hpp"

class ImageTexture : public Texture {
private:
  int width, height;
  unsigned char *image;
  float scale;

public:
  ImageTexture(const std::string &path, float scale, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
    int bpp;
    image = stbi_load(path.c_str(), &width, &height, &bpp, 3);
    scale = 255;
    this->scale = scale;
  }

  Color get_color(float x, float y) const {
    auto int_x = static_cast<int>(round(scale * x) - height / 2);
    auto int_y = static_cast<int>(round(scale * y) - width / 2);
    auto xx = (int_x % height + height) % height;
    auto yy = (int_y % width + width) % width;
    auto pos = 3 * width * xx + 3 * yy;
    return Color(image[pos] / 255., image[pos + 1] / 255., image[pos + 2] / 255.);
  }
};