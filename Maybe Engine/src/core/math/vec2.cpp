#include "vec2.h"

namespace mb {

	Vec2::Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	
	Vec2::Vec2()
		: x(0), y(0)
	{

	}

	Vec2 Vec2::Add(const Vec2& other) const
	{
		Vec2 result(x + other.x, y + other.y);

		return result;
	}

	Vec2 Vec2::Add(float scalar) const
	{
		Vec2 result(x + scalar, y + scalar);

		return result;
	}

	Vec2 Vec2::Mul(const Vec2& other) const
	{
		Vec2 result(x * other.x, y * other.y);
		
		return result;
	}

	Vec2 Vec2::Mul(float scalar) const
	{
		Vec2 result(x * scalar, y * scalar);

		return result;
	}

	Vec2 Vec2::operator+=(const Vec2& other)
	{
		Vec2 result = Add(other);
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator+=(float scalar)
	{
		Vec2 result = Add(scalar);
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator-=(const Vec2& other)
	{
		Vec2 result = Add({ -other.x, -other.y });
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator-=(float scalar)
	{
		Vec2 result = Add(-scalar);
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator*=(const Vec2& other)
	{
		Vec2 result = Mul(other);
		this->x = result.x;
		this->y = result.y;
	
		return result;
	}

	Vec2 Vec2::operator*=(float scalar)
	{
		Vec2 result = Mul(scalar);
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator/=(const Vec2& other)
	{
		Vec2 result = Mul({ 1 / other.x, 1 / other.y});
		this->x = result.x;
		this->y = result.y;

		return result;
	}

	Vec2 Vec2::operator/=(float scalar)
	{
		Vec2 result = Mul(1 / scalar);
		this->x = result.x;
		this->y = result.y;
	
		return result;
	}

	float Vec2::Dot(const Vec2& other) const 
	{
		return (x * other.x) + (y * other.y);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vec)
	{
		stream << "{" << vec.x << ", " << vec.y << "}";
		return stream;
	}

}