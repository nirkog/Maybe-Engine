#include "vec4.h"

namespace mb { namespace maths {

	Vec4::Vec4()
		: x(0), y(0), z(0), w(0)
	{

	}

	const Vec4 Vec4::Add(const Vec4& other) const
	{
		Vec4 result(x + other.x, y + other.y, z + other.z, w + other.w);

		return result;
	}

	const Vec4 Vec4::Add(float scalar) const
	{
		Vec4 result(x + scalar, y + scalar, z + scalar, w + scalar);

		return result;
	}

	const Vec4 Vec4::Mul(const Vec4& other) const
	{
		Vec4 result(x * other.x, y * other.y, z * other.z, w * other.w);

		return result;
	}

	const Vec4 Vec4::Mul(float scalar) const
	{
		Vec4 result(x * scalar, y * scalar, z * scalar, w * scalar);

		return result;
	}

	const Vec4 Vec4::operator+=(const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	const Vec4 Vec4::operator+=(float scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
	
		return *this;
	}

	const Vec4 Vec4::operator-=(const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	const Vec4 Vec4::operator-=(float scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
	
		return *this;
	}
	
	const Vec4 Vec4::operator*=(const Vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
	
		return *this;
	}

	const Vec4 Vec4::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
	
		return *this;
	}

	const Vec4 Vec4::operator*=(const Mat4& mat)
	{
		const maths::Vec4 newVec = *this * mat;

		this->x = newVec.x;
		this->y = newVec.y;
		this->z = newVec.z;
		this->w = newVec.w;

		return *this;
	}

	const Vec4 Vec4::operator/=(const Vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		
		return *this;
	}

	const Vec4 Vec4::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

	const Vec4 Vec4::Normalize() const
	{
		Vec4 result(x, y, z, w);
		result /= Magnitude();

		return result;
	}

	const Vec4 Vec4::operator*(const Mat4& mat) const
	{
		float ogValues[4];
		ogValues[0] = x;
		ogValues[1] = y;
		ogValues[2] = z;
		ogValues[3] = w;

		float values[4];
		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 0;

		for (unsigned short i = 0; i < 4; i++)
		{
			for (unsigned short j = 0; j < 4; j++)
			{
				values[i] += ogValues[j] * mat[i][j];
			}
		}
		
		Vec4 result(values[0], values[1], values[2], values[3]);

		return result;
	}

	void Vec4::SetAt(unsigned int i, const float& val)
	{
		switch (i)
		{
		case 0:
			this->x = val;
			break;
		case 1:
			this->y = val;
			break;
		case 2:
			this->z = val;
			break;
		case 3:
			this->w = val;
			break;
		default:
			std::cout << "Error: Out Of Range At SetAt()!" << std::endl;
			break;
		}
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4& vec)
	{
		stream << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
		return stream;
 	}

} }