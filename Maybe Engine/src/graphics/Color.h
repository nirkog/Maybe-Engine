#pragma once

#include <string.h>

#include "..\maths\vec4.h"

namespace mb { namespace graphics {

	class Color
	{
	public:
		Color();
		Color(float r, float g, float b, float a);
		Color(const char* hex);

		const maths::Vec4 ToVec4() const { return {r, g, b, a}; };

		friend std::ostream& operator<<(std::ostream& stream, const Color& color);
	public:
		float r, g, b, a;
	};

} }