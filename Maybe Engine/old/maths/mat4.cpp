#include "mat4.h"

namespace mb { namespace maths {

	Mat4::Mat4()
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j)
					m_Data[i][j] = 1;
				else
					m_Data[i][j] = 0;
			}
		}

		//std::cout << sizeof(m_Data);
	}

	Mat4::Mat4(const float k)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j)
					m_Data[i][j] = k;
				else
					m_Data[i][j] = 0;
			}
		}
	}

	Mat4::Mat4(const Mat4& other)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				m_Data[i][j] = other[i][j];
			}
		}
	}

	const Mat4 Mat4::Add(float scalar) const
	{
		Mat4 result(*this);

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i][j] += scalar;
			}
		}

		return result;
	}

	const Mat4 Mat4::Add(const Mat4& other) const
	{
		Mat4 result(*this);

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i][j] += other[i][j];
			}
		}

		return result;
	}

	const Mat4 Mat4::Mul(float scalar) const
	{
		Mat4 result(*this);

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i][j] *= scalar;
			}
		}

		return result;
	}

	const Mat4 Mat4::Mul(const Mat4& other) const
	{
		Mat4 result;

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				float item = 0;
				for (unsigned int k = 0; k < 4; k++)
				{
					//std::cout << m_Data[i][k] * other[k][j] << std::endl;
					item += m_Data[i][k] * other[k][j];
					//std::cout << item << std::endl;
				}

				result[i][j] = item;
			}
		}

		return result;
	}

	float* Mat4::operator[](unsigned int i) const
	{
		return (float*) m_Data[i];
	}

	void Mat4::Print() const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				std::cout << m_Data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& stream, const Mat4& mat)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				stream << mat[i][j] << " ";
			}
			stream << std::endl;
		}

		return stream;
	}

	const Mat4 Mat4::Transpose() const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i][j] = m_Data[j][i];
			}
		}

		return result;
	}

	const Mat4 Mat4::translate(const Mat4& mat, const Vec3& translateVec)
	{
		Mat4 translationMat;
		translationMat[0][3] = translateVec.x;
		translationMat[1][3] = translateVec.y;
		translationMat[2][3] = translateVec.z;

		return mat * translationMat;
	}

	const Mat4 Mat4::scale(const Mat4& mat, const Vec3& scaleVec)
	{
		Mat4 scaleMat;
		scaleMat[0][0] = scaleVec.x;
		scaleMat[1][1] = scaleVec.y;
		scaleMat[2][2] = scaleVec.z;

		return mat * scaleMat;
	}

	const Mat4 Mat4::rotate(const Mat4& mat, float theta, const Vec3& axis)
	{
		Vec3 normAxis = axis.Normalize();
		Mat4 rotationMat;
		rotationMat[0][0] = cos(theta) + pow(normAxis.x, 2) * (1 - cos(theta));
		rotationMat[0][1] = normAxis.x * normAxis.y * (1 - cos(theta)) - normAxis.z * sin(theta);
		rotationMat[0][2] = normAxis.x * normAxis.z * (1 - cos(theta)) + normAxis.y * sin(theta);
		rotationMat[1][0] = normAxis.y * normAxis.x * (1 - cos(theta)) + normAxis.z * sin(theta);
		rotationMat[1][1] = cos(theta) + pow(normAxis.y, 2) * (1 - cos(theta));
		rotationMat[1][2] = normAxis.y * normAxis.z * (1 - cos(theta)) - normAxis.x * sin(theta);
		rotationMat[2][0] = normAxis.z * normAxis.x * (1 - cos(theta)) - normAxis.y * sin(theta);
		rotationMat[2][1] = normAxis.z * normAxis.y * (1 - cos(theta)) - normAxis.x * sin(theta);
		rotationMat[2][2] = cos(theta) + pow(normAxis.z, 2) * (1 - cos(theta));

		return mat * rotationMat;
	}

	const Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 result;
		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = -2 / (far - near);
		result[0][3] = -(right + left) / (right - left);
		result[1][3] = -(top + bottom) / (top - bottom);
		result[2][3] = -(far + near) / (far - near);

		return result;
	}

} }