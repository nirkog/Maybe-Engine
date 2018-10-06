#include "input.h"

namespace mb { namespace input {

	Key Input::keys[] = { Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M, UP, DOWN, LEFT, RIGHT };
	std::vector<Key> Input::upKeys, Input::downKeys, Input::pressedKeys, Input::releasedKeys;
	unsigned int keyCount = 0;

	void Input::Init()
	{
		keyCount = sizeof(keys) / sizeof(Key);

		for (unsigned int i = 0; i < keyCount; i++)
		{
			upKeys.push_back(keys[i]);
		}
	}

	void Input::Update(const graphics::Window& window)
	{
		for (unsigned int i = 0; i < releasedKeys.size(); i++)
		{
			upKeys.push_back(releasedKeys[i]);
		}
		releasedKeys.clear();

		std::vector<Key> newKeys;

		for (unsigned int i = 0; i < upKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*)window.GetGLFWwindow(), upKeys[i]) == GLFW_PRESS)
			{
				downKeys.push_back(upKeys[i]);
				newKeys.push_back(upKeys[i]);
				pressedKeys.push_back(upKeys[i]);
				upKeys.erase(upKeys.begin() + i);
				i--;
			}
		}

		//std::cout << "Updated up, ";

		for (unsigned int i = 0; i < downKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*)window.GetGLFWwindow(), downKeys[i]) == GLFW_PRESS)
			{
				bool newKey = false;
				for (unsigned int j = 0; j < newKeys.size(); j++)
					if (newKeys[i] == downKeys[i]) { newKey = true; break; }

				if (!newKey)
				{
					downKeys.erase(downKeys.begin() + i);
					i--;
				}
			}
		}

		//std::cout << "updated down, ";

		for (unsigned int i = 0; i < pressedKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*)window.GetGLFWwindow(), pressedKeys[i]) != GLFW_PRESS)
			{
				releasedKeys.push_back(pressedKeys[i]);
				pressedKeys.erase(pressedKeys.begin() + i);
				i--;
			}
		}

		//std::cout << "updated pressed." << std::endl;

		//std::cout << "Pressed Keys: " << pressedKeys.size() << ", Down Keys: " << downKeys.size() << ", Up Keys: " << upKeys.size() << std::endl;
		//std::cout << "Pressed key is " << pressedKeys[0] << std::endl;
	}

	bool Input::IsKeyPressed(Key key)
	{
		for (unsigned int i = 0; i < pressedKeys.size(); i++)
		{
			if (pressedKeys[i] == key)
				return true;
		}

		return false;
	}

	bool Input::IsKeyDown(Key key)
	{
		for (unsigned int i = 0; i < downKeys.size(); i++)
		{
			if (downKeys[i] == key)
				return true;
		}

		return false;
	}

	bool Input::IsKeyUp(Key key)
	{
		//std::cout << key;
		for (unsigned int i = 0; i < upKeys.size(); i++)
		{
			if (upKeys[i] == key)
				return true;
		}

		return false;
	}

	bool Input::IsKeyReleased(Key key)
	{
		for (unsigned int i = 0; i < releasedKeys.size(); i++)
		{
			if (releasedKeys[i] == key)
				return true;
		}

		return false;
	}

} }