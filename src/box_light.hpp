#pragma once

#include "light.hpp"
#include "point_light.hpp"
#include "utility.hpp"

class BoxLight : public Light {
private:
  std::vector<const Light*> lights;

public:
  Vector position, size;

  BoxLight(const Color &color, float intensity, const Vector &position, const Vector &size, unsigned sample = 16) : Light(color, intensity) {
    this->position = position;
    this->size = size;
    for (unsigned i = 0; i < sample; ++i) {
      for (unsigned j = 0; j < sample; ++j) {
        Vector ratio((i + randf()) / sample, randf(), (j + randf()) / sample);
        this->lights.emplace_back(new PointLight(color, intensity, position + ratio * size));
      }
    }
  }

  float intersect(const Ray &ray) const {
    Vector d = ray.direction, o = ray.source;
    Vector p1 = position, p2 = position + size;
    float distances[] = {
      d.x ? (p1.x - o.x) / d.x : 0,
      d.x ? (p2.x - o.x) / d.x : 0,
      d.y ? (p1.y - o.y) / d.y : 0,
      d.y ? (p2.y - o.y) / d.y : 0,
      d.z ? (p1.z - o.z) / d.z : 0,
      d.z ? (p2.z - o.z) / d.z : 0
    };
    float distance = std::numeric_limits<float>::max();
    for (unsigned i = 0; i < 6; ++i) {
      if (distances[i] == 0) {
        continue;
      }
      Vector p = o + distances[i] * d;
      if (p.x < p1.x - numeric_eps || p.x > p2.x + numeric_eps) {
        continue;
      }
      if (p.y < p1.y - numeric_eps || p.y > p2.y + numeric_eps) {
        continue;
      }
      if (p.z < p1.z - numeric_eps || p.z > p2.z + numeric_eps) {
        continue;
      }
      if (distances[i] < distance) {
        distance = distances[i];
      }
    }
    return distance;
  };

  IlluminateResult illuminate(const Vector &position, const std::vector<const Object*> &objects) const {
    auto direction = Vector::ZERO;
    auto intensity = Color::ZERO;
    for (auto &light : lights) {
      auto result = light->illuminate(position, objects);
      direction += result.direction;
      intensity += result.intensity;
    }
    return {.direction = direction.normalize(), .intensity = intensity / lights.size()};
  }
};