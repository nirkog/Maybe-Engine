#pragma once

#include <iostream>
#include <gl\glew.h>
#include <glfw\glfw3.h>

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error! error code " << error << std::endl;
		std::cout << "At file " << file << ", on line " << line << ", in function " << function << "()!" << std::endl;
		std::cin.get();
		return false;
	}

	return true;
}

#define DEBUG 1

#ifndef ASSERT
#define ASSERT(x) if (!(x)) __debugbreak;
#endif

#ifndef GLCall
#if _DEBUG
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#else
#define GLCall(x) x;
#endif
#endif