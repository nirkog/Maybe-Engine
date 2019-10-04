#pragma once

#include <iostream>

#include "Vec2.h"

namespace mb {
	class Vec3
	{
	public:
		Vec3(float x, float y, float z);
		Vec3(const Vec2& vec, float z);
		Vec3();

		Vec3 Add(const Vec3& other) const;
		Vec3 Add(float scalar) const;

		Vec3 Mul(const Vec3& other) const;
		Vec3 Mul(float scalar) const;

		inline Vec3 operator+(const Vec3& other) const { return Add(other); }
		inline Vec3 operator+(float scalar) const { return Add(scalar); }
		Vec3 operator+=(const Vec3& other);
		Vec3 operator+=(float scalar);

		inline Vec3 operator-(const Vec3& other) const { return Add(other.Mul(-1)); }
		inline Vec3 operator-(float scalar) const { return Add(-scalar); }
		Vec3 operator-=(const Vec3& other);
		Vec3 operator-=(float scalar);

		inline Vec3 operator*(const Vec3& other) const { return Mul(other); }
		inline Vec3 operator*(float scalar) const { return Mul(scalar); }
		Vec3 operator*=(const Vec3& other);
		Vec3 operator*=(float scalar);

		inline Vec3 operator/(const Vec3& other) const { return Mul({1 / other.x, 1 / other.y, 1 / other.z}); }
		inline Vec3 operator/(float scalar) const { return Mul(1 / scalar); }
		Vec3 operator/=(const Vec3& other);
		Vec3 operator/=(float scalar);

		float Dot(const Vec3& other) const;

		inline float Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
		
		Vec3 Normalize() const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec3& vec);

	public:
		float x, y, z;
	};
}