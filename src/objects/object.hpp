#pragma once

#include "../textures/texture.hpp"
#include "../libraries/vector.hpp"
#include "../textures/texture.hpp"
#include "../libraries/intersection.hpp"

class Ray;

class Object {
public:
  const Texture* texture;

  Object(const Texture* texture) {
    this->texture = texture;
  }

  virtual ~Object() {
    delete texture;
  }

  virtual Intersection intersect(const Ray &ray) const = 0;

  virtual Vector get_normal(const Ray &ray, const Intersection &intersection) const = 0;

  virtual Color get_color(const Vector &position) const = 0;
};