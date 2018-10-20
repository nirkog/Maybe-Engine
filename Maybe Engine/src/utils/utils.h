#pragma once

//#include <GL\glew.h>

#include "Time.h"
#include "..\input\input.h"

namespace mb { namespace utils {

	extern void Init();
	extern void Terminate();

	extern void Update(const graphics::Window& window);

} }