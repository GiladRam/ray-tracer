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
  PolygonMesh(const std::string &path, float scale, const Vector &delta, const Material &material) : Object(material) {
    std::ifstream ifs(path, std::ios::in);
    if (path.substr(path.length() - 4) == ".obj") {
      for (std::string buffer; ifs >> buffer; ) {
        if (buffer == "v") {
          float x, y, z;
          ifs >> x >> y >> z;
          vertices.emplace_back(x, y, z);
        } else if (buffer == "f") {
          int indices[3];
          for (auto i = 0; i < 3; ++i) {
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
      vertex = vertex * scale + delta;
    }
    for (auto &face : faces) {
      auto a = std::get<0>(face);
      auto b = std::get<1>(face);
      auto c = std::get<2>(face);
      objects.emplace_back(new Triangle(vertices[a], vertices[b], vertices[c], material));
    }
    if (faces.size() > 30) {
      // mesh smoothing
      auto count = std::vector<int>(vertices.size(), 0);
      normals = std::vector<Vector>(vertices.size(), Vector::ZERO);
      for (auto i = 0; i < faces.size(); ++i) {
        auto a = std::get<0>(faces[i]);
        auto b = std::get<1>(faces[i]);
        auto c = std::get<2>(faces[i]);
        normals[a] += objects[i]->get_normal(Vector::ZERO, Ray(Vector::ZERO, Vector::ZERO));
        normals[b] += objects[i]->get_normal(Vector::ZERO, Ray(Vector::ZERO, Vector::ZERO));
        normals[c] += objects[i]->get_normal(Vector::ZERO, Ray(Vector::ZERO, Vector::ZERO));
        count[a]++;
        count[b]++;
        count[c]++;
      }
      for (auto i = 0; i < vertices.size(); ++i) {
        normals[i] /= count[i];
      }
    }
  }

  float intersect(const Ray &ray) const {
    auto distance = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      auto length = object->intersect(ray);
      if (length < distance) {
        distance = length;
      }
    }
    return distance;
  }

  Vector get_normal(const Vector &position, const Ray &ray) const {
    auto distance = std::numeric_limits<float>::max();
    auto i = 0;
    for (auto j = 0; j < faces.size(); ++j) {
      auto face_normal = objects[j]->get_normal(position, ray);
      auto length = objects[j]->intersect(ray);
      if (length < distance) {
        distance = length;
        i = j;
      }
    }
    if (!normals.empty()) {
      auto vectorP = ray.direction.det(objects[i]->pointC - objects[i]->pointA);
      auto det = vectorP.dot(objects[i]->pointB - objects[i]->pointA);
      auto vectorT = ray.source - objects[i]->pointA;
      auto u = vectorT.dot(vectorP) / det;
      auto vectorQ = vectorT.det(objects[i]->pointB - objects[i]->pointA);
      auto v = ray.direction.dot(vectorQ) / det;
      auto a = std::get<0>(faces[i]);
      auto b = std::get<1>(faces[i]);
      auto c = std::get<2>(faces[i]);
      return ((1 - u - v) * normals[a] + u * normals[b] + v * normals[c]).normalize();
    } else {
      return objects[i]->get_normal(position, ray);
    }
  }
};