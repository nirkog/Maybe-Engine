#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace mb { namespace maths {

	extern float radians(float degrees);
	extern float sin(float theta);
	extern float cos(float theta);
	extern float tan(float theta);
	extern float abs(float num);

} }