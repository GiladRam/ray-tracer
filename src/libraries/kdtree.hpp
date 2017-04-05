#pragma once

#include "../objects/triangle.hpp"

class KDNode {
public:
  int axis;
  KDNode* child[2];
  std::vector<const Triangle*> objects;
  std::vector<Vector> corners;
  float pivot;

  KDNode(int axis, const std::vector<const Triangle*>& objects) {
    this->axis = axis;
    this->child[0] = nullptr;
    this->child[1] = nullptr;
    this->objects = objects;
    this->corners = {
      std::numeric_limits<float>::max() * Vector(1, 1, 1),
      std::numeric_limits<float>::min() * Vector(1, 1, 1)
    };
    this->pivot = 0;
    if (!objects.empty()) {
      for (auto &object : objects) {
        for (auto &vertex : object->points) {
          pivot += vertex[axis] / (objects.size() * 3);
          for (auto i = 0; i < 3; ++i) {
            if (vertex[i] < corners[0][i]) {
              corners[0][i] = vertex[i];
            }
            if (vertex[i] > corners[1][i]) {
              corners[1][i] = vertex[i];
            }
          }
        }
      }
    }
  }

  ~KDNode() {
    delete child[0];
    delete child[1];
  }
};

class KDTree {
private:
  KDNode* root;

  KDNode* build(const std::vector<const Triangle*> &objects, int depth) const {
    KDNode* node = new KDNode(depth % 3, objects);
    if (objects.size() > 128 && depth < 8) {
      std::vector<const Triangle*> left, right;
      for (auto &object : objects) {
        for (auto i = 0; i < 3; ++i) {
          if (object->points[i][node->axis] <= node->pivot) {
            left.emplace_back(object);
            break;
          }
        }
        for (auto i = 0; i < 3; ++i) {
          if (object->points[i][node->axis] >= node->pivot) {
            right.emplace_back(object);
            break;
          }
        }
      }
      auto common = left.size() + right.size() - objects.size();
      if (common * 4 < objects.size()) {
        node->child[0] = build(left, depth + 1);
        node->child[1] = build(right, depth + 1);
      }
    }
    return node;
  }

  float intersect(const Ray &ray, KDNode* node, float threshold, int depth) const {
    auto d = ray.direction, s = ray.source;
    auto p1 = node->corners[0], p2 = node->corners[1];
    float distances[] = {
      d.x ? (p1.x - s.x) / d.x : 0,
      d.x ? (p2.x - s.x) / d.x : 0,
      d.y ? (p1.y - s.y) / d.y : 0,
      d.y ? (p2.y - s.y) / d.y : 0,
      d.z ? (p1.z - s.z) / d.z : 0,
      d.z ? (p2.z - s.z) / d.z : 0
    };
    auto length = std::numeric_limits<float>::max();
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
      if (distances[i] < length) {
        length = distances[i];
      }
    }
    if (length >= threshold) {
      return threshold;
    }
    auto distance = threshold;
    if (node->child[0] && node->child[1]) {
      auto point = ray.source + distance * ray.direction;
      auto prefer = point[node->axis] <= node->pivot ? 0 : 1;
      for (auto i : {prefer, prefer ^ 1}) {
        auto length = intersect(ray, node->child[i], distance, depth + 1);
        if (length < distance) {
          distance = length;
        }
      }
    } else {
      for (auto &object : node->objects) {
        auto length = object->intersect(ray);
        if (length < distance) {
          distance = length;
        }
      }
    }
    return distance;
  }

public:
  KDTree(const std::vector<const Triangle*> &objects) {
    root = build(objects, 0);
  }

  ~KDTree() {
    delete root;
  }

  float intersect(const Ray &ray) const {
    return intersect(ray, root, std::numeric_limits<float>::max(), 0);
  }
};