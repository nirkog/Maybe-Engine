#pragma once

#include <iostream>

#include "AL\al.h"
#include "AL\alc.h"

namespace mb { namespace audio {
	static void ALClearError()
	{
		while (alGetError() != AL_NO_ERROR);
	}

	static const char* ErrorCodeToString(ALenum error)
	{
		switch (error) {
		case AL_NO_ERROR:
			return "AL_NO_ERROR";
		case AL_INVALID_NAME:
			return "AL_INVALID_NAME";
		case AL_INVALID_ENUM:
			return "AL_INVALID_ENUM";
		case AL_INVALID_VALUE:
			return "AL_INVALID_VALUE";
		case AL_INVALID_OPERATION:
			return "AL_INVALID_OPERATION";
		case AL_OUT_OF_MEMORY:
			return "AL_OUT_OF_MEMORY";
		default:
			return "No such error code";
		}
	}

	static bool ALLogCall(const char* function, const char* file, int line)
	{
		ALenum error;
		while ((error = alGetError()) != AL_NO_ERROR)
		{
			std::cout << "OpenAL Error! error code " << ErrorCodeToString(error) << std::endl;
			std::cout << "At file " << file << ", on line " << line << ", in function " << function << "()!" << std::endl;
			std::cin.get();
			return false;
		}

		return true;
	}

	#ifndef ASSERT
	#define ASSERT(x) if (!(x)) __debugbreak();
	#endif

	#ifndef ALCall
	#if _DEBUG
	#define ALCall(x) ALClearError();\
			x;\
			ASSERT(ALLogCall(#x, __FILE__, __LINE__));
	#else
	#define ALCall(x) x;
	#endif
	#endif
}}