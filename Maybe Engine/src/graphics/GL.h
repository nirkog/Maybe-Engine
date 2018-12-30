#pragma once

#include <iostream>
#include <gl\glew.h>
#include <glfw\glfw3.h>

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static const char* ErrorCodeToString(GLenum error)
{
	const char* strings[8] = {
		"GL_INVALID_ENUM",
		"GL_INVALID_VALUE",
		"GL_INVALID_OPERATION",
		"GL_STACK_OVERFLOW",
		"GL_STACK_UNDERFLOW",
		"GL_OUT_OF_MEMORY",
		"GL_INVALID_FRAMEBUFFER_OPERATION",
		"GL_CONTEXT_LOST"
	};

	if (error >= 1280 && error <= 1287)
		return strings[error - 1280];

	return "Unknown error code!";
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error! error code " << ErrorCodeToString(error) << std::endl;
		std::cout << "At file " << file << ", on line " << line << ", in function " << function << "()!" << std::endl;
		std::cin.get();
		return false;
	}

	return true;
}

#ifndef ASSERT
#define ASSERT(x) if (!(x)) __debugbreak();
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