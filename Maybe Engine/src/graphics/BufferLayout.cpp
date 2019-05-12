#include "BufferLayout.h"

namespace mb { namespace graphics {

	unsigned int GetTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_FLOAT_MAT4:
			return sizeof(float) * 4 * 4;
		}

		return 0;
	}

} }