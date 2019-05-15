#pragma once

//#include <GL\glew.h>

#include "Time.h"
#include "File.h"
#include "..\input\input.h"
#include "..\graphics\GL.h"
//#include "..\audio\AL.h"

namespace mb { namespace utils {

	extern void Init();
	extern void Terminate();

	extern void Update(const graphics::Window* window);

	extern void LogOpenGLDetails();

} }