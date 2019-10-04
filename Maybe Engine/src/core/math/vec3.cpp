#include "vec3.h"

namespace mb {
	
	Vec3::Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3::Vec3(const Vec2& vec, float z)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = z;
	}

	Vec3::Vec3()
		: x(0), y(0), z(0)
	{

	}

	Vec3 Vec3::Add(const Vec3& other) const
	{
		Vec3 result(x + other.x, y + other.y, z + other.z);

		return result;
	}

	Vec3 Vec3::Add(float scalar) const
	{
		Vec3 result(x + scalar, y + scalar, z + scalar);

		return result;
	}

	Vec3 Vec3::Mul(const Vec3& other) const
	{
		Vec3 result(x * other.x, y * other.y, z * other.z);

		return result;
	}

	Vec3 Vec3::Mul(float scalar) const
	{
		Vec3 result(x * scalar, y * scalar, z * scalar);

		return result;
	}

	Vec3 Vec3::operator+=(const Vec3& other)
	{
		Vec3 result = *this + other;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator+=(float scalar)
	{
		Vec3 result = *this + scalar;
		x = result.x;
		y = result.y;
		z = result.z;
	
		return result;
	}

	Vec3 Vec3::operator-=(const Vec3& other)
	{
		Vec3 result = *this - other;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator-=(float scalar)
	{
		Vec3 result = *this - scalar;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator*=(const Vec3& other)
	{
		Vec3 result = *this * other;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator*=(float scalar)
	{
		Vec3 result = *this * scalar;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator/=(const Vec3& other)
	{
		Vec3 result = *this / other;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	Vec3 Vec3::operator/=(float scalar)
	{
		Vec3 result = *this / scalar;
		x = result.x;
		y = result.y;
		z = result.z;

		return result;
	}

	float Vec3::Dot(const Vec3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	Vec3 Vec3::Normalize() const
	{
		Vec3 result(*this);
		result.x /= Magnitude();
		result.y /= Magnitude();
		result.z /= Magnitude();

		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vec)
	{
		stream << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
		return stream;
	}

}