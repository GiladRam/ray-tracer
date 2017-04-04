#pragma once

#include "../textures/texture.hpp"
#include "../libraries/vector.hpp"
#include "../textures/texture.hpp"

class Ray;

class Object {
public:
  const Texture* texture;

  Object(const Texture *texture) {
    this->texture = texture;
  }

  virtual float intersect(const Ray &ray) const = 0;

  virtual Vector get_normal(const Vector &position, const Ray &ray) const = 0;

  virtual Color get_color(const Vector &position) const = 0;
};