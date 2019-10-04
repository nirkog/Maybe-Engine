#pragma once

#include <iostream>

namespace mb {

	class Color
	{
	public:
		Color();
		Color(float r, float g , float b, float a);
		~Color();

		Color Grayscale() const;
		Color Invert() const;

		Color operator!() const;

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Color& color);
	public:
		float r, g, b, a;
		
		static Color Black;
		static Color White;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Yellow;
	};

}