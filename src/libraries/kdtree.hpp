#pragma once

#include "../objects/triangle.hpp"

class KDTree {
public:
  struct Node {
    Node* child[2];
    std::vector<const Triangle*> objects;
    std::vector<Vector> corners;
    Node() {
      child[0] = child[1] = nullptr;
      corners = {Vector(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()), Vector(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min())};
    }
  };

  Node *root;
  static constexpr int NUM_LEAF_OBJS = 10;
  static constexpr int NUM_MAX_DEPTH = 10;
  KDTree(): root(nullptr) {}
  ~KDTree() { delete root; }

  void build(const std::vector<const Triangle*> &triangles) {
    delete root;
    root = build(triangles, 0);
  }

  float find_nearest(const Ray &ray) const {
    return find_nearest(ray, root, std::numeric_limits<float>::max());
  }

public:

  float get_split_plane_naive(const std::vector<const Triangle*> &triangles, int axis) const {
    float sum = 0;
    for (const Triangle *t : triangles) {
      for (int i = 0; i < 3; ++i) {
        sum += t->points[i][axis];
      }
    }
    return sum / (3 * triangles.size());
  }

  Node *build(const std::vector<const Triangle*> &triangles, int depth) const {
    Node *node = new Node();
    for (const Triangle *t : triangles) {
      for (auto &vertex : t->points) {
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
    if (triangles.size() >= NUM_LEAF_OBJS && depth < NUM_MAX_DEPTH) {
      int axis = depth % 3;
      float plane = get_split_plane_naive(triangles, axis);
      int common = 0;
      std::vector<const Triangle*> lef, rig;
      for (const Triangle *t : triangles) {
        bool in_lef = t->points[0][axis] <= plane || t->points[1][axis] <= plane || t->points[2][axis] <= plane;
        bool in_rig = t->points[0][axis] >= plane || t->points[1][axis] >= plane || t->points[2][axis] >= plane;
        if (in_lef) lef.emplace_back(t);
        if (in_rig) rig.emplace_back(t);
        if (in_lef && in_rig) ++common;
      }
      if (common * 2 < triangles.size()) {
        node->child[0] = build(lef, depth + 1);
        node->child[1] = build(rig, depth + 1);
        return node;
      }
    }

    // if too few triangles, or too deep, or too many common triangles
    node->objects = triangles;
    return node;
  }

  float find_nearest(const Ray &ray, Node *node, float opt_dist) const {
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
    if (distance >= opt_dist) {
      return distance;
    }
    distance = std::numeric_limits<float>::max();
    if (node->child[0] || node->child[1]) {
      distance = std::min(distance, find_nearest(ray, node->child[0], opt_dist));
      opt_dist = std::min(opt_dist, distance);
      distance = std::min(distance, find_nearest(ray, node->child[1], opt_dist));
      opt_dist = std::min(opt_dist, distance);
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
};