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

} }