#include "utils.h"

namespace mb { namespace utils {

	void Init()
	{
		glfwInit();
		input::Input::Init();
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
} }