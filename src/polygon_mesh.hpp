#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include "object.hpp"
#include "triangle.hpp"

class PolygonMesh : public Object {
private:
  std::vector<const Triangle*> objects;

public:
  PolygonMesh(const std::string &path, const Material &material) : Object(material) {
    std::ifstream ifs(path, std::ios::in);
    if (path.substr(path.length() - 4) == ".obj") {
      std::vector<Vector> vertices;
      for (std::string buffer; ifs >> buffer; ) {
        if (buffer == "v") {
          float x, y, z;
          ifs >> x >> y >> z;
          vertices.emplace_back(x, y, z);
        } else if (buffer == "f") {
          unsigned indices[3];
          for (unsigned i = 0; i < 3; ++i) {
            ifs >> buffer;
            std::istringstream iss(buffer);
            iss >> indices[i];
            --indices[i];
          }
          objects.emplace_back(new Triangle(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]], material));
        }
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
    auto normal = Vector::ZERO;
    float minimum = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      float cos = object->get_normal(position).dot(position - object->pointA);
      if (fabsf(cos) < minimum) {
        normal = object->get_normal(position);
        minimum = fabsf(cos);
      }
    }
    return normal.normalize();
  }
};