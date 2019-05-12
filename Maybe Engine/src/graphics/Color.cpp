#include "Color.h"

namespace mb { namespace graphics {

	Color::Color()
		: r(0), g(0), b(0), a(0)
	{
	}

	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{
	}

	Color::Color(const char* hex)
	{
		if (hex[0] != '#')
		{
			std::cout << "Color hex does not start with #!" << std::endl;
			r = 0, g = 0, b = 0, a = 0;
		}

		char chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
		char vals[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

		a = 1.0f;

		for (unsigned int i = 0; i < (strlen(hex) - 1) / 2; i++)
		{
			unsigned int value = 0;
			char code[2] = {hex[i * 2 + 1], hex[i * 2 + 2]};

			for (unsigned int j = 0; j < 16; j++)
			{
				if (code[1] == chars[j])
					value += vals[j];
				if (code[0] == chars[j])
					value += vals[j] * 16;
			}
			
			switch (i)
			{
			case 0:
				r = value / 255.0f;
				break;
			case 1:
				g = value / 255.0f;
				break;
			case 2:
				b = value / 255.0f;
				break;
			case 3:
				a = value / 255.0f;
				break;
			}
		}
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << color.r << ", " << color.g << ", " << color.b << ", " << color.a;
		return stream;
	}

} }