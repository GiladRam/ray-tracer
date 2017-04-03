//#pragma once
//
//#include "../libraries/color.hpp"
//#include "texture.hpp"
//#include "../externals/pngio.hpp"
//
//class ImageTexture : public Texture {
//private:
//  ImageRGB image;
//  float scale;
//
//public:
//  ImageTexture(const std::string &path, float scale, float k_diffusive, float k_diffusive_reflective, float k_specular, float k_reflective, float k_refractive, float k_refractive_index) : Texture(k_diffusive, k_diffusive_reflective, k_specular, k_reflective, k_refractive, k_refractive_index) {
//    this->image = readpng(path);
//    this->scale = scale;
//  }
//
//  Color get_color(float x, float y) const {
//    auto int_x = static_cast<int>(round(scale * x) - image.height / 2);
//    auto int_y = static_cast<int>(round(scale * y) - image.width / 2);
//    auto xx = (int_x % image.height + image.height) % image.height;
//    Color col = img.get(, (int_y % img.size.w + img.size.w) % img.size.w);
//    return col;
//  }
//};