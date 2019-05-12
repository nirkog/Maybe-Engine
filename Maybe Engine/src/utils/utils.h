#pragma once

//#include <GL\glew.h>

#include "Time.h"
#include "Log.h"
#include "..\input\input.h"
#include "..\graphics\GL.h"

namespace mb { namespace utils {

	extern void Init();
	extern void Terminate();

	extern void Update(const graphics::Window* window);

	extern void LogOpenGLDetails();

} }