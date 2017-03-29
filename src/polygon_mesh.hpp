#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "object.hpp"
#include "triangle.hpp"

class PolygonMesh : public Object {
private:
  std::vector<const Object*> objects;

public:
  PolygonMesh(const std::string &path, const Material &material) : Object(material) {
    std::ifstream ifs(path, std::ios::in);
    std::vector<Vector> vertices;
    for (std::string buffer; ifs >> buffer; ) {
      if (buffer == "v") {
        float x, y, z;
        ifs >> x >> y >> z;
        vertices.emplace_back(x * 4, y * 4, z * 4 - 15);
//        vertices.emplace_back(x, y, z);
      } else if (buffer == "f") {
        int v[3];
        for (int i = 0; i < 3; ++i) {
          ifs >> buffer;
          sscanf(buffer.c_str(), "%d", &v[i]);
          --v[i];
        }
        objects.emplace_back(new Triangle(vertices[v[0]], vertices[v[1]], vertices[v[2]], material));
      }
    }
  }

  float intersect(const Ray &ray) const {
    float distance = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      float length = object->intersect(ray);
      if (length < distance) {
        distance = length;
      }
    }
    return distance;
  }

  Vector get_normal(const Vector &position) const {
    Vector normal = Vector::ZERO;
    float minimum = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      const Triangle* triangle = (const Triangle*)object;
      auto vector = triangle->get_normal(position);
      float dot = vector.dot(position - triangle->pointA);
      if (fabsf(dot) < fabsf(minimum)) {
        normal = vector;
        minimum = dot;
      }
    }
    return normal.normalize();
  }
};