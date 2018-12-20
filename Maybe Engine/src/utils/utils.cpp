#include "utils.h"

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
		GLCall(std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl);
		GLCall(std::cout << "Running on a " << glGetString(GL_RENDERER) << std::endl);
	}
} }