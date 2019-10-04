#pragma once

#include <math.h>
#include <cstdlib>
#include <ctime>

#define MATH_PI 3.14159265359

namespace mb {

	class Math
	{
	public:
		static double Sin(double x);
		static double Cos(double x);
		static double Tan(double x);
		static double Sinh(double x);
		static double Cosh(double x);
		static double Tanh(double x);
		static double Asin(double x);
		static double Acos(double x);
		static double Atan(double x);
		static double Atan2(double y, double x);
		static double Exp(double x);
		static double Lan(double x);
		static double Log10(double x);
		static double Modf(double x, double* integer);
		static double Pow(double x, double y);
		static double Sqrt(double x);
		static double Abs(double x);
		static double Ceil(double x);
		static double Floor(double x);
		static double Fmod(double x, double y);
		static double Max(double x, double y);
		static double Min(double x, double y);

		static double Round(double x);
		static double Clamp(double value, double min, double max);
		static double Lerp(double a, double b, double t);
		static bool Sign(double x);

		static double ToRadians(double degrees);
		static double ToDegrees(double radians);

		static void Seed(unsigned int seed);
		static double Rand();
		static int Randint(int min, int max);
	public:
		static double Pi;
		static int RandMax;
	private:
		static bool s_Seeded;
	};

}