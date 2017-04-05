#pragma once

#include "../objects/triangle.hpp"

class KDNode {
public:
  KDNode* child[2];
  std::vector<const Triangle*> objects;
  std::vector<Vector> corners;
  int axis;
  float plane;

  KDNode() {
    child[0] = child[1] = nullptr;
    corners = {Vector(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()), Vector(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min())};
  }
};

class KDTree {
private:
  KDNode *root;

  KDNode* build(const std::vector<const Triangle*> &objects, int depth = 0) const {
    KDNode* node = new KDNode();
    for (auto &object : objects) {
      for (auto &vertex : object->points) {
        for (auto i = 0; i < 3; ++i) {
          if (vertex[i] < node->corners[0][i]) {
            node->corners[0][i] = vertex[i];
          }
          if (vertex[i] > node->corners[1][i]) {
            node->corners[1][i] = vertex[i];
          }
        }
      }
    }
    node->axis = depth % 3;
    if (objects.size() >= 100 && depth < 10) {
      float sum = 0;
      for (auto &t : objects) {
        for (int i = 0; i < 3; ++i) {
          sum += t->points[i][node->axis];
        }
      }
      node->plane = sum / (3 * objects.size());
      std::vector<const Triangle*> left, right;
      for (auto &object : objects) {
        for (auto i = 0; i < 3; ++i) {
          if (object->points[i][node->axis] <= node->plane) {
            left.emplace_back(object);
            break;
          }
        }
        for (auto i = 0; i < 3; ++i) {
          if (object->points[i][node->axis] >= node->plane) {
            right.emplace_back(object);
            break;
          }
        }
      }
      auto common = left.size() + right.size() - objects.size();
      if (common * 4 < objects.size()) {
        node->child[0] = build(left, depth + 1);
        node->child[1] = build(right, depth + 1);
        return node;
      }
    }
    node->objects = objects;
    return node;
  }

  float intersect(const Ray &ray, KDNode *node, float opt_dist, int depth = 0) const {
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
    auto point = s + distance * d;
    if (distance >= opt_dist) {
      return distance;
    }
    distance = opt_dist;
    if (node->child[0] || node->child[1]) {
      if (point[node->axis] <= node->plane) {
        distance = std::min(distance, intersect(ray, node->child[0], distance));
        distance = std::min(distance, intersect(ray, node->child[1], distance));
      } else {
        distance = std::min(distance, intersect(ray, node->child[1], distance));
        distance = std::min(distance, intersect(ray, node->child[0], distance));
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
    root = build(objects);
  }

  ~KDTree() {
    delete root;
  }

  float intersect(const Ray &ray) const {
    return intersect(ray, root, std::numeric_limits<float>::max());
  }
};