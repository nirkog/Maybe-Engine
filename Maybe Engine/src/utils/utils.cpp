#include "utils.h"

#include "Log.h"

namespace mb { namespace utils {

	void Init()
	{
		glfwInit();
		input::Input::Init();
		Log::Init();
	}

	void Terminate()
	{
		glfwTerminate();
	}

	void Update(const graphics::Window& window)
	{
		Time::Update();
		input::Input::Update(window);
	}

	void LogOpenGLDetails()
	{
		GLCall(Log::Debug("Using OpenGL version {}", glGetString(GL_VERSION)));
		GLCall(Log::Debug("Running on a {}", glGetString(GL_RENDERER)));
	}
} }