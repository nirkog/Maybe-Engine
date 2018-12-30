#pragma once

#include <math.h>
#include <iostream>

#include "Mat4.h"

namespace mb { namespace maths {

	class Vec4
	{
	public:
		inline Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		Vec4();

		const Vec4 Add(const Vec4& other) const;
		const Vec4 Add(float scalar) const;

		const Vec4 Mul(const Vec4& other) const;
		const Vec4 Mul(float scalar) const;

		inline Vec4 operator+(const Vec4& other) const { return Add(other); }
		inline Vec4 operator+(float scalar) const { return Add(scalar); }
		const Vec4 operator+=(const Vec4& other);
		const Vec4 operator+=(float scalar);

		inline Vec4 operator-(const Vec4& other) const { return Add(other.Mul(-1)); }
		inline Vec4 operator-(float scalar) const { return Add(-scalar); }
		const Vec4 operator-=(const Vec4& other);
		const Vec4 operator-=(float scalar);

		inline Vec4 operator*(const Vec4& other) const { return Mul(other); }
		inline Vec4 operator*(float scalar) const { return Mul(scalar); }
		const Vec4 operator*(const Mat4& mat) const;
		const Vec4 operator*=(const Vec4& other);
		const Vec4 operator*=(float scalar);
		const Vec4 operator*=(const Mat4& mat);

		inline Vec4 operator/(const Vec4& other) const { return Mul(Vec4(1 / other.x, 1 / other.y, 1 / other.z, 1 / other.w)); }
		inline Vec4 operator/(float scalar) const { return Mul(1 / scalar); }
		const Vec4 operator/=(const Vec4& other);
		const Vec4 operator/=(float scalar);

		inline float Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)); }

		const Vec4 Normalize() const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec4& vec);
	
	public:
		float x, y, z, w;
	};

} }