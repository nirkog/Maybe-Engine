#include "Color.h"

namespace mb {

	Color Color::Black = Color(0, 0, 0, 1);
	Color Color::White = Color(1, 1, 1, 0);
	Color Color::Red = Color(1, 0, 0, 1);
	Color Color::Green = Color(0, 1, 0, 1);
	Color Color::Blue = Color(0, 0, 1, 1);
	Color Color::Yellow = Color(1, 0.92f, 0.016f, 1);

	Color::Color()
		: r(0), g(0), b(0), a(0)
	{

	}

	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{

	}

	Color::~Color()
	{

	}

	Color Color::Grayscale() const
	{
		Color result;
		float average = (r + g + b) / 3.0f;
		result.r = average;
		result.g = average;
		result.b = average;
		result.a = a;

		return result;
	}

	Color Color::Invert() const
	{
		Color result;
		result.r = 1.0f - r;
		result.g = 1.0f - g;
		result.b = 1.0f - b;
		result.a = a;

		return result;
	}

	Color Color::operator!() const
	{
		return Invert();
	}

	bool Color::operator==(const Color& other) const
	{
		if (r == other.r && g == other.g && b == other.b && a == other.a)
			return true;
		return false;
	}

	bool Color::operator!=(const Color& other) const
	{
		if (r != other.r || g != other.g || b != other.b || a != other.a)
			return true;
		return false;
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << "{" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "}";
		return stream;
	}
}