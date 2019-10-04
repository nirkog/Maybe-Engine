#include "Input.h"

namespace mb {

	bool Input::IsKeyPressed(KeyCode key)
	{
		int state = glfwGetKey(Application::GetInstance()->GetWindow().GetGLFWwindow(), (int) key);
		
		return state == GLFW_PRESS;
	}

	Vec2 Input::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(Application::GetInstance()->GetWindow().GetGLFWwindow(), &x, &y);

		return { (float) x, (float) y };
	}

	bool Input::IsMouseButtonPressed(MouseButton button)
	{
		int state = glfwGetMouseButton(Application::GetInstance()->GetWindow().GetGLFWwindow(), (int) button);

		return state == GLFW_PRESS;
	}
}