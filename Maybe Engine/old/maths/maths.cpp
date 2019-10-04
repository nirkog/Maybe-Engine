#include "maths.h"

float sinImp(float theta)
{
	return sin(theta);
}

float cosImp(float theta)
{
	return cos(theta);
}

float tanImp(float theta)
{
	return tan(theta);
}

namespace mb { namespace maths {

	float radians(float degrees)
	{
		return degrees / 180 * (float) M_PI;
	}

	float sin(float theta)
	{
		return sinImp(theta);
	}

	float cos(float theta)
	{
		return cosImp(theta);
	}

	float tan(float theta)
	{
		return tanImp(theta);
	}

	float abs(float num)
	{
		return (num > 0) ? num : -num;
	}

} }