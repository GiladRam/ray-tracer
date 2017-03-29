#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include "object.hpp"
#include "triangle.hpp"

class PolygonMesh : public Object {
private:
  std::vector<Vector> vertices, normals;
  std::vector<std::tuple<int, int, int>> faces;
  std::vector<const Triangle*> objects;

public:
  PolygonMesh(const std::string &path, float scale, const Material &material) : Object(material) {
    std::ifstream ifs(path, std::ios::in);
    if (path.substr(path.length() - 4) == ".obj") {
      for (std::string buffer; ifs >> buffer; ) {
        if (buffer == "v") {
          float x, y, z;
          ifs >> x >> y >> z;
          vertices.emplace_back(x, y, z);
        } else if (buffer == "f") {
          int indices[3];
          for (int i = 0; i < 3; ++i) {
            ifs >> buffer;
            std::istringstream iss(buffer);
            iss >> indices[i];
            --indices[i];
          }
          faces.emplace_back(indices[0], indices[1], indices[2]);
        }
      }
    }
    for (auto &vertex : vertices) {
      vertex *= scale;
    }
    for (auto &face : faces) {
      int a = std::get<0>(face);
      int b = std::get<1>(face);
      int c = std::get<2>(face);
      objects.emplace_back(new Triangle(vertices[a], vertices[b], vertices[c], material));
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
      auto face_normal = object->get_normal(position);
      float cos = face_normal.dot(position - object->pointA);
      if (fabsf(cos) < minimum) {
        normal = face_normal;
        minimum = fabsf(cos);
      }
    }
    return normal.normalize();
  }
};