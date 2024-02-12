#pragma once
#include "../external/imgui/imgui.h"
#include <Windows.h>
#include <cmath>
#include <numbers>
#include <string>
#include <vector>

#define M_PI 3.14159265358979323846264338327950288419716939937510
static ULONG ww = GetSystemMetrics(SM_CXSCREEN);
static ULONG wh = GetSystemMetrics(SM_CYSCREEN);

class FVector2 {
	float x, y;
	FVector2() : x(0.f), y(0.f) {}
	FVector2(float x_, float y_) : x(x_), y(y_) {}
	FVector2(ImVec2 ImVec2_) : x(ImVec2_.x), y(ImVec2_.y) {}
	FVector2 operator=(ImVec2 ImVec2_) {
		x = ImVec2_.x;
		y = ImVec2_.y;
		return *this;
	}
	FVector2 operator+(FVector2 Vec2_) { return { x + Vec2_.x, y + Vec2_.y }; }
	FVector2 operator-(FVector2 Vec2_) { return { x - Vec2_.x, y - Vec2_.y }; }
	FVector2 operator*(FVector2 Vec2_) { return { x * Vec2_.x, y * Vec2_.y }; }
	FVector2 operator/(FVector2 Vec2_) { return { x / Vec2_.x, y / Vec2_.y }; }
	FVector2 operator*(float n) { return { x / n, y / n }; }
	FVector2 operator/(float n) { return { x / n, y / n }; }
	bool operator==(FVector2 Vec2_) { return x == Vec2_.x && y == Vec2_.y; }
	bool operator!=(FVector2 Vec2_) { return x != Vec2_.x || y != Vec2_.y; }
	ImVec2 ToImVec2() { return ImVec2(x, y); }
	float Length() { return sqrtf(powf(x, 2) + powf(y, 2)); }
	float DistanceTo(const FVector2& Pos) { return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2)); }
};

struct FQuaternion {
	float x, y, z, w;
};



struct ViewMatrix {
	float* operator[](int index) { return matrix[index]; }

	float matrix[4][4];
};


struct FVector3 {
	// constructor
	constexpr FVector3(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept : x(x), y(y), z(z) {}

	// operator overloads
	constexpr const FVector3& operator-(const FVector3& other) const noexcept { return FVector3{ x - other.x, y - other.y, z - other.z }; }

	constexpr const FVector3& operator+(const FVector3& other) const noexcept { return FVector3{ x + other.x, y + other.y, z + other.z }; }

	constexpr const FVector3& operator/(const float factor) const noexcept { return FVector3{ x / factor, y / factor, z / factor }; }

	constexpr const FVector3& operator*(const float factor) const noexcept { return FVector3{ x * factor, y * factor, z * factor }; }

	constexpr const bool operator>(const FVector3& other) const noexcept { return x > other.x && y > other.y && z > other.z; }

	constexpr const bool operator>=(const FVector3& other) const noexcept { return x >= other.x && y >= other.y && z >= other.z; }

	constexpr const bool operator<(const FVector3& other) const noexcept { return x < other.x && y < other.y && z < other.z; }

	constexpr const bool operator<=(const FVector3& other) const noexcept { return x <= other.x && y <= other.y && z <= other.z; }
	constexpr const bool operator==(const FVector3& other) const noexcept { return x == other.x && y == other.y && z == other.z; }


	float distance(const FVector3& other) const noexcept {
		const FVector3 diff = *this - other;
	
		return std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
	}

	constexpr const FVector3& toAngle() const noexcept {
		return FVector3{ std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>), std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>), 0.0f };
	}

	constexpr const bool isZero() const noexcept { return x == 0.f && y == 0.f && z == 0.f; }

	FVector3 world_to_screen(ViewMatrix matrix) const {
		float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
		float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];

		float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;


		float screen_x = ww * 0.5f;
		float screen_y = wh * 0.5f;

		screen_x += 0.5f * _x * ww + 0.5f;
		screen_y -= 0.5f * _y * wh + 0.5f;


		return { screen_x, screen_y, w };
	}

	// struct data
	float x, y, z;
};

inline bool world_to_screen(const FVector3& pos, FVector3& out, ViewMatrix matrix) {
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