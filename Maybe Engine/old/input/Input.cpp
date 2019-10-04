#include "input.h"

namespace mb { namespace input {

	Key Input::keys[] = { ESCAPE_KEY, Q_KEY, W_KEY, E_KEY, R_KEY, T_KEY, Y_KEY, U_KEY, I_KEY, O_KEY, P_KEY, A_KEY, S_KEY, D_KEY, F_KEY, G_KEY, H_KEY, J_KEY, K_KEY, L_KEY, Z_KEY, X_KEY, C_KEY, V_KEY, B_KEY, N_KEY, M_KEY, UP_KEY, DOWN_KEY, LEFT_KEY, RIGHT_KEY, SPACE_KEY };
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

	void Input::Update(const graphics::Window* window)
	{
		for (unsigned int i = 0; i < releasedKeys.size(); i++)
		{
			upKeys.push_back(releasedKeys[i]);
		}
		releasedKeys.clear();

		std::vector<Key> newKeys;

		for (unsigned int i = 0; i < upKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*)window->GetGLFWwindow(), upKeys[i]) == GLFW_PRESS)
			{
				downKeys.push_back(upKeys[i]);
				newKeys.push_back(upKeys[i]);
				pressedKeys.push_back(upKeys[i]);
				upKeys.erase(upKeys.begin() + i);
				i--;
			}
		}

		for (unsigned int i = 0; i < downKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*) window->GetGLFWwindow(), downKeys[i]) == GLFW_PRESS)
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

		for (unsigned int i = 0; i < pressedKeys.size(); i++)
		{
			if (glfwGetKey((GLFWwindow*) window->GetGLFWwindow(), pressedKeys[i]) != GLFW_PRESS)
			{
				releasedKeys.push_back(pressedKeys[i]);
				pressedKeys.erase(pressedKeys.begin() + i);
				i--;
			}
		}
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