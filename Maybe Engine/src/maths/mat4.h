#pragma once

#include <iostream>

namespace mb { namespace maths {

	class Mat4
	{
	public:
		Mat4();
		Mat4(float k);
		Mat4(const Mat4& other);

		const Mat4 Add(float scalar) const;
		const Mat4 Add(const Mat4& other) const;

		const Mat4 Mul(float scalar) const;
		const Mat4 Mul(const Mat4& other) const;

		inline Mat4 operator+(float scalar) const { return Add(scalar); }
		inline Mat4 operator+(const Mat4& other) const { return Add(other); }

		inline Mat4 operator-(float scalar) const { return Add(-scalar); }
		inline Mat4 operator-(const Mat4& other) const { return Add(other.Mul(-1)); }

		inline Mat4 operator*(float scalar) const { return Mul(scalar); }
		inline Mat4 operator*(const Mat4& other) const { return Mul(other); }

		float* operator[](unsigned int i) const;

		void Print() const;
		friend std::ostream& operator<<(std::ostream& stream, const Mat4& mat);

		inline float* GetData() const { return (float*) m_Data; }

		const Mat4 Transpose() const;
	private:
		float m_Data[4][4];
	};

} }