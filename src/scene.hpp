#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "externals/concurrentqueue.hpp"
#include "camera.hpp"
#include "lights/light.hpp"
#include "objects/object.hpp"
#include "libraries/color.hpp"
#include "libraries/utility.hpp"
#include "libraries/ray.hpp"

class Scene {
public:
  struct {
    int trace_depth = 3;
    float trace_bias = 1e-4;
    int diffusive_reflection_depth = 2;
    int diffusive_reflection_sample = 1024;
    int thread_worker = std::thread::hardware_concurrency();
    Color environment_color = Color::GRAY;
  } config;

private:
  const Camera* camera;
  std::vector<const Light*> lights;
  std::vector<const Object*> objects;
  Color* frame;

  Color trace(const Ray &ray, float refractive_index = 1, int depth = 0) const {
    if (depth > config.trace_depth) {
      return config.environment_color;
    }
    auto distance = std::numeric_limits<float>::max();
    const Object* object = nullptr;
    const Light* light = nullptr;
    for (auto &o : objects) {
      auto length = o->intersect(ray);
      if (length < distance) {
        distance = length;
        object = o;
      }
    }
    for (auto &l : lights) {
      auto length = l->intersect(ray);
      if (length < distance) {
        distance = length;
        light = l;
      }
    }
    if (light != nullptr) {
      return light->color;
    }
    if (object == nullptr) {
      return config.environment_color;
    }
    auto color = Color::ZERO;
    auto point = ray.source + ray.direction * distance;
    auto normal = object->get_normal(point, ray);
    for (auto &l : lights) {
      auto illuminate = l->illuminate(point + normal * config.trace_bias, objects);
      // diffusive shading
      if (object->texture->k_diffusive > 0) {
        auto dot = std::max(.0f, normal.dot(-illuminate.direction));
        color += object->texture->k_diffusive * illuminate.intensity * dot;
      }
      // specular shading (phong's model)
      if (object->texture->k_specular > 0) {
        auto reflective_direction = ray.direction.reflect(normal);
        auto dot = std::max(.0f, ray.direction.dot(reflective_direction));
        color += object->texture->k_specular * illuminate.intensity * powf(dot, 20.f);
      }
    }
    // diffusive reflection
    if (object->texture->k_diffusive_reflective > 0 && depth < config.diffusive_reflection_depth) {
      auto dy = normal;
      auto dx = (fabsf(dy.x) > fabsf(dy.y) ? Vector(dy.z, 0, -dy.x) : Vector(0, -dy.z, dy.y)).normalize();
      auto dz = dy.det(dx).normalize();
      auto sum = Color::ZERO;
      for (auto i = 0; i < config.diffusive_reflection_sample; ++i) {
        auto cos = randf();
        auto sin = sqrtf(1 - cos * cos);
        auto phi = randf() * 2 * numeric_pi;
        auto rotate = Vector(sin * cosf(phi), cos, sin * sinf(phi));
        auto reflective_direction = Vector(
          rotate.x * dx.x + rotate.y * dy.x + rotate.z * dz.x,
          rotate.x * dx.y + rotate.y * dy.y + rotate.z * dz.y,
          rotate.x * dx.z + rotate.y * dy.z + rotate.z * dz.z
        ).normalize();
        auto reflective_ray = Ray(point + reflective_direction * config.trace_bias, reflective_direction);
        sum += object->texture->k_diffusive_reflective * trace(reflective_ray, refractive_index, depth + 1);
      }
      color += sum / config.diffusive_reflection_sample;
    }
    // reflection
    if (object->texture->k_reflective > 0) {
      auto reflective_direction = ray.direction.reflect(normal);
      auto reflective_ray = Ray(point + reflective_direction * config.trace_bias, reflective_direction);
      color += object->texture->k_reflective * trace(reflective_ray, refractive_index, depth + 1);
    }
    // refraction
    if (object->texture->k_refractive > 0) {
      auto refractive_direction = ray.direction.refract(normal, refractive_index / object->texture->k_refractive_index);
      if (refractive_direction != Vector::INVALID) {
        auto refractive_ray = Ray(point + refractive_direction * config.trace_bias, refractive_direction);
        color += object->texture->k_refractive * trace(refractive_ray, object->texture->k_refractive_index, depth + 1);
      }
    }
    return config.environment_color + color * object->get_color(point);
  }

public:
  Scene(const Camera* camera) {
    this->camera = camera;
    this->frame = new Color[camera->height * camera->width];
  }

  void add(const Light* light) {
    lights.emplace_back(light);
  }

  void add(const Object* object) {
    objects.emplace_back(object);
  }

  void render() {
    auto start = std::chrono::high_resolution_clock::now();
    std::cerr << "start rendering with " << config.thread_worker << " thread workers";
    moodycamel::ConcurrentQueue<std::pair<int, int>> queue;
    for (auto y = 0; y < camera->height; ++y) {
      for (auto x = 0; x < camera->width; ++x) {
        queue.enqueue(std::make_pair(x, y));
      }
    }
    std::vector<std::thread> workers;
    std::atomic<int> count(0);
    srand((unsigned)time(nullptr));
    for (auto i = 0; i < config.thread_worker; ++i) {
      workers.emplace_back([&] {
        for (std::pair<int, int> item; queue.try_dequeue(item); ++count) {
          auto x = item.first, y = item.second;
          frame[y * camera->width + x] = trace(camera->ray(x, y));
        }
      });
    }
    for (int i; (i = count.load()) < camera->width * camera->height; ) {
      auto now = std::chrono::high_resolution_clock::now();
      std::cerr << "\rrendered " << i << "/" << camera->width * camera->height
                << " pixels with " << config.thread_worker << " thread workers"
                << " in " << (now - start).count() / 1e9 << " seconds";
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    for (auto &worker : workers) {
      worker.join();
    }
    auto now = std::chrono::high_resolution_clock::now();
    std::cerr << std::endl << "done in " << (now - start).count() / 1e9 << " seconds" << std::endl;
  }

  void save(const std::string &path) const {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    ofs << "P3" << std::endl;
    ofs << camera->width << " " << camera->height << std::endl;
    ofs << "255" << std::endl;
    for (auto i = 0; i < camera->height * camera->width; ++i) {
      ofs << static_cast<int>(clamp(frame[i].x, 0, 1) * 255) << " "
          << static_cast<int>(clamp(frame[i].y, 0, 1) * 255) << " "
          << static_cast<int>(clamp(frame[i].z, 0, 1) * 255) << std::endl;
    }
    ofs.close();
  }
};