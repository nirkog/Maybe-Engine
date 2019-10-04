#pragma once

#include <iostream>

namespace mb {

	class Vec2 
	{
	public:
		Vec2(float x, float y);
		Vec2();

		Vec2 Add(const Vec2& other) const;
		Vec2 Add(float scalar) const;

		Vec2 Mul(const Vec2& other) const;
		Vec2 Mul(float scalar) const;

		inline Vec2 operator+(const Vec2& other) const { return Add(other); }
		inline Vec2 operator+(float scalar) const { return Add(scalar); }
		Vec2 operator+=(const Vec2& other);
		Vec2 operator+=(float scalar);

		inline Vec2 operator-(const Vec2& other) const { return Add({ -other.x, -other.y }); }
		inline Vec2 operator-(float scalar) const { return Add(-scalar); }
		Vec2 operator-=(const Vec2& other);
		Vec2 operator-=(float scalar);

		inline Vec2 operator*(const Vec2& other) const { return Mul(other); }
		inline Vec2 operator*(float scalar) const { return Mul(scalar); }
		Vec2 operator*=(const Vec2& other);
		Vec2 operator*=(float scalar);

		inline Vec2 operator/(const Vec2& other) const { return Mul({ 1 / other.x, 1 / other.y }); }
		inline Vec2 operator/(float scalar) const { return Mul(1 / scalar); }
		Vec2 operator/=(const Vec2& other);
		Vec2 operator/=(float scalar);

		float Dot(const Vec2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& vec);
	public:
		float x, y;
	};
}