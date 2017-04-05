#pragma once

#include <vector>
#include <fstream>
#include "object.hpp"
#include "triangle.hpp"
#include "../libraries/kdtree.hpp"

class PolygonMesh : public Object {
private:
  std::vector<Vector> vertices, normals;
  std::vector<std::vector<int>> faces;
  std::vector<const Triangle*> objects;
  std::vector<Vector> corners;
  KDTree* kdtree;

public:
  PolygonMesh(const std::string &path, const Vector &position, float size, const Texture *texture) : Object(texture) {
    if (path.substr(path.length() - 4) == ".obj") {
      std::ifstream ifs(path, std::ios::in);
      for (std::string buffer; ifs >> buffer; ) {
        if (buffer == "v") {
          float x, y, z;
          ifs >> x >> y >> z;
          vertices.emplace_back(x, y, z);
        } else if (buffer == "f") {
          faces.emplace_back(std::vector<int>(3, 0));
          for (auto i = 0; i < 3; ++i) {
            ifs >> faces.back()[i];
            faces.back()[i]--;
          }
        }
      }
      ifs.close();
    }
    // transformation
    auto center = Vector::ZERO;
    auto minimum = vertices.front(), maximum = vertices.front();
    for (auto &vertex : vertices) {
      center += vertex / vertices.size();
      for (auto i = 0; i < 3; ++i) {
        if (vertex[i] < minimum[i]) {
          minimum[i] = vertex[i];
        }
        if (vertex[i] > maximum[i]) {
          maximum[i] = vertex[i];
        }
      }
    }
    auto scale = std::numeric_limits<float>::max();
    for (auto i = 0; i < 3; ++i) {
      auto ratio = size / (maximum[i] - minimum[i]);
      if (ratio < scale) {
        scale = ratio;
      }
    }
    for (auto &vertex : vertices) {
      vertex = (vertex - center) * scale + position;
    }
    for (auto &face : faces) {
      objects.emplace_back(new Triangle({vertices[face[0]], vertices[face[1]], vertices[face[2]]}, texture));
    }
    // mesh smoothing
    if (faces.size() > 32) {
      normals = std::vector<Vector>(vertices.size(), Vector::ZERO);
      auto counts = std::vector<int>(vertices.size(), 0);
      for (auto i = 0; i < faces.size(); ++i) {
        for (auto j = 0; j < 3; ++j) {
          auto x = faces[i][j];
          normals[x] += objects[i]->normal;
          counts[x]++;
        }
      }
      for (auto i = 0; i < vertices.size(); ++i) {
        normals[i] /= counts[i];
      }
    }
    corners = {(minimum - center) * scale + position, (maximum - center) * scale + position};
    kdtree = new KDTree();
    kdtree->build(objects);
  }

  float intersect(const Ray &ray) const {
    return kdtree->find_nearest(ray);
    auto d = ray.direction, s = ray.source;
    auto p1 = corners[0], p2 = corners[1];
    float distances[] = {
      d.x ? (p1.x - s.x) / d.x : 0,
      d.x ? (p2.x - s.x) / d.x : 0,
      d.y ? (p1.y - s.y) / d.y : 0,
      d.y ? (p2.y - s.y) / d.y : 0,
      d.z ? (p1.z - s.z) / d.z : 0,
      d.z ? (p2.z - s.z) / d.z : 0
    };
    auto distance = std::numeric_limits<float>::max();
    for (auto i = 0; i < 6; ++i) {
      if (distances[i] == 0) {
        continue;
      }
      auto p = s + distances[i] * d;
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
    if (distance == std::numeric_limits<float>::max()) {
      return distance;
    }
    distance = std::numeric_limits<float>::max();
    for (auto &object : objects) {
      auto length = object->intersect(ray);
      if (length < distance) {
        distance = length;
      }
    }
    return distance;
  }

  Vector get_normal(const Vector &position, const Ray &ray) const {
    auto index = 0;
    auto distance = std::numeric_limits<float>::max();
    for (auto i = 0; i < faces.size(); ++i) {
      auto length = objects[i]->intersect(ray);
      if (length < distance) {
        distance = length;
        index = i;
      }
    }
    auto face = faces[index];
    auto object = objects[index];
    if (normals.empty()) {
      return object->normal;
    }
    auto vectorP = ray.direction.det(object->points[2] - object->points[0]);
    auto vectorT = ray.source - object->points[0];
    auto vectorQ = vectorT.det(object->points[1] - object->points[0]);
    auto det = vectorP.dot(object->points[1] - object->points[0]);
    auto u = vectorT.dot(vectorP) / det;
    auto v = ray.direction.dot(vectorQ) / det;
    return (1 - u - v) * normals[face[0]] + u * normals[face[1]] + v * normals[face[2]];
  }

  Color get_color(const Vector &position) const {
    // fixme: calculate the texture coordinate for polygon mesh
    return texture->get_color(0, 0);
  }
};