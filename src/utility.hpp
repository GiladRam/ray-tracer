#pragma once

#include <thread>
#include <cstdlib>
#include <algorithm>

const unsigned num_thread_worker = std::thread::hardware_concurrency();
const unsigned num_trace_depth = 10;
const unsigned num_area_light_sample = 16;
const float trace_bias = 1e-4;
const float numeric_eps = 1e-6;

inline float randf() {
  return rand() / static_cast<float>(RAND_MAX);
}

inline float clamp(float x, float l, float r) {
  return std::min(std::max(x, l), r);
}