/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef FEATURES_MATH_H_
#define FEATURES_MATH_H_

#include <Windows.h>
#include "GLFW/glfw3.h"
#include <algorithm>
#include <cmath>
#include <numbers>
#include <vector>
#include "imgui/imgui_internal.h"
#include "imgui/imgui.h"

// TODO: change this to be cross-platform ;
static int ww = GetSystemMetrics(SM_CXSCREEN);
static int wh = GetSystemMetrics(SM_CYSCREEN);


struct ViewMatrix {
  float *operator[](int index) { return matrix[index]; }

  float matrix[4][4];
};

struct Vector3 {
  // constructor
  constexpr Vector3(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept : x(x), y(y), z(z) {}

  // operator overloads
  constexpr const Vector3 &operator-(const Vector3 &other) const noexcept { return Vector3{x - other.x, y - other.y, z - other.z}; }

  constexpr const Vector3 &operator+(const Vector3 &other) const noexcept { return Vector3{x + other.x, y + other.y, z + other.z}; }

  constexpr const Vector3 &operator/(const float factor) const noexcept { return Vector3{x / factor, y / factor, z / factor}; }

  constexpr const Vector3 &operator*(const float factor) const noexcept { return Vector3{x * factor, y * factor, z * factor}; }

  constexpr const bool operator>(const Vector3 &other) const noexcept { return x > other.x && y > other.y && z > other.z; }

  constexpr const bool operator>=(const Vector3 &other) const noexcept { return x >= other.x && y >= other.y && z >= other.z; }

  constexpr const bool operator<(const Vector3 &other) const noexcept { return x < other.x && y < other.y && z < other.z; }

  constexpr const bool operator<=(const Vector3 &other) const noexcept { return x <= other.x && y <= other.y && z <= other.z; }
  constexpr const bool operator==(const Vector3 &other) const noexcept { return x == other.x && y == other.y && z == other.z; }

  float distance(const Vector3 &other) const noexcept {
    const Vector3 diff = *this - other;

    return std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
  }

  constexpr const Vector3 &to_angle() const noexcept {
    return Vector3{std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>), std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>), 0.0f};
  }

  constexpr const bool is_zero() const noexcept { return x == 0.f && y == 0.f && z == 0.f; }

  constexpr const bool invalid() const noexcept { return !x || !y || !z; }

  const bool valid_num() const noexcept { return !std::isnan(x) && !std::isinf(x) && !std::isnan(y) && !std::isinf(y) && !std::isnan(z) && !std::isinf(z); }

  Vector3 world_to_screen(ViewMatrix matrix) const {


    float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
    float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
    float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

    if (w < 0.001f)
      return {};

    float inv_w = 1.f / w;
    _x *= inv_w;
    _y *= inv_w;

    float screen_x = ww * 0.5f;
    float screen_y = wh * 0.5f;

    screen_x += 0.5f * _x * ww + 0.5f;
    screen_y -= 0.5f * _y * wh + 0.5f;

    return {screen_x, screen_y, w};
  }

  // struct data
  float x, y, z;
};

inline bool world_to_screen(const Vector3 &pos, Vector3 &out, ViewMatrix matrix) {
  out.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
  out.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

  float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

  if (w < 0.01f)
    return false;

  float inv_w = 1.f / w;
  out.x *= inv_w;
  out.y *= inv_w;

  float x = ww * 0.5f;
  float y = wh * 0.5f;

  x += 0.5f * out.x * ww + 0.5f;
  y -= 0.5f * out.y * wh + 0.5f;

  out.x = x;
  out.y = y;

  return true;
}

#endif // FEATURES_MATH_H_
