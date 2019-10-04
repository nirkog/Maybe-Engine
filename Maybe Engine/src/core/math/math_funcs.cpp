#include "math_funcs.h"

namespace mb {

	double Math::Pi = MATH_PI;
	int Math::RandMax = RAND_MAX;
	bool Math::s_Seeded = false;

	double Math::Sin(double x)
	{
		return ::sin(x);
	}

	double Math::Cos(double x)
	{
		return ::cos(x);
	}

	double Math::Tan(double x)
	{
		return ::tan(x);
	}

	double Math::Sinh(double x)
	{
		return ::sinh(x);
	}

	double Math::Cosh(double x)
	{
		return ::cosh(x);
	}

	double Math::Tanh(double x)
	{
		return ::tanh(x);
	}

	double Math::Asin(double x)
	{
		return ::asin(x);
	}

	double Math::Acos(double x)
	{
		return ::acos(x);
	}

	double Math::Atan(double x)
	{
		return ::atan(x);
	}

	double Math::Atan2(double y, double x)
	{
		return ::atan2(y, x);
	}

	double Math::Exp(double x)
	{
		return ::exp(x);
	}

	double Math::Lan(double x)
	{
		return ::log(x);
	}

	double Math::Log10(double x)
	{
		return ::log10(x);
	}

	double Math::Modf(double x, double* integer)
	{
		return ::modf(x, integer);
	}

	double Math::Pow(double x, double y)
	{
		return ::pow(x, y);
	}

	double Math::Sqrt(double x)
	{
		return ::sqrt(x);
	}

	double Math::Abs(double x)
	{
		return ::abs(x);
	}

	double Math::Ceil(double x)
	{
		return ::ceil(x);
	}

	double Math::Floor(double x)
	{
		return ::floor(x);
	}

	double Math::Fmod(double x, double y)
	{
		return ::fmod(x, y);
	}

	double Math::Max(double x, double y)
	{
		return ::fmax(x, y);
	}

	double Math::Min(double x, double y)
	{
		return ::fmin(x, y);
	}

	double Math::Round(double x)
	{
		if (x > 0) {
			return ::floor(x + 0.5);
		}
		else {
			x = -x;
			return -::floor(x + 0.5);
		}
	}

	double Math::Clamp(double value, double min, double max)
	{
		if (value > max) return max;
		else if (value < min) return min;

		return value;
	}

	double Math::Lerp(double a, double b, double t)
	{
		t = Clamp(t, 0, 1);

		return a + ((b - a) * t);
	}

	bool Math::Sign(double x)
	{
		return (x >= 0) ? true : false;
	}

	double Math::ToRadians(double degrees)
	{
		return (degrees / 180.0) * Pi;
	}

	double Math::ToDegrees(double radians)
	{
		return (radians * 180.0) / Pi;
	}

	void Math::Seed(unsigned int seed)
	{
		if (!s_Seeded) s_Seeded = true;
	
		std::srand(seed);
	}

	double Math::Rand()
	{
		if (!s_Seeded) Seed((unsigned int) std::time(nullptr));

		return (double) std::rand() / (double) RAND_MAX;
	}

	int Math::Randint(int min, int max)
	{
		return min + (std::rand() % (max - min + 1));
	}

}