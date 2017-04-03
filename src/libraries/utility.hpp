#pragma once

#include <cstdlib>
#include <algorithm>

const float numeric_eps = 1e-8;

inline float randf() {
  return rand() / static_cast<float>(RAND_MAX);
}

inline float clamp(float x, float l, float r) {
  return std::min(std::max(x, l), r);
}

inline float modulo(float x) {
  return x - std::floor(x);
}

inline int modulo(int x, int mod) {
  return (x % mod + mod) % mod;
}