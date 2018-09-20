#pragma once

//#include <vector>
#include <GLFW\glfw3.h>

#include "..\graphics\graphics.h"

namespace mb { namespace input {

	enum Key 
	{
		Q = GLFW_KEY_Q,
		W = GLFW_KEY_W,
		E = GLFW_KEY_E,
		R = GLFW_KEY_R,
		T = GLFW_KEY_T,
		Y = GLFW_KEY_Y,
		U = GLFW_KEY_U,
		I = GLFW_KEY_I,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		Z = GLFW_KEY_Z,
		X = GLFW_KEY_X,
		C = GLFW_KEY_C,
		V = GLFW_KEY_V,
		B = GLFW_KEY_B,
		N = GLFW_KEY_N,
		M = GLFW_KEY_M,
		UP = GLFW_KEY_UP,
		DOWN = GLFW_KEY_DOWN,
		LEFT = GLFW_KEY_LEFT,
		RIGHT = GLFW_KEY_RIGHT
	};

	Key keys[] = 
	{
		Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M, UP, DOWN, LEFT, RIGHT
	};

	unsigned int keyCount;
	std::vector<Key> upKeys, downKeys, pressedKeys, releasedKeys;

	void Init()
	{
		keyCount = sizeof(keys) / sizeof(Key);

		for (unsigned int i = 0; i < keyCount; i++)
		{
			upKeys.push_back(keys[i]);
		}
	}

	void Update(const graphics::Window& window)
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
			if(glfwGetKey((GLFWwindow*)window.GetGLFWwindow(), pressedKeys[i]) != GLFW_PRESS)
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

	bool IsKeyPressed(Key key)
	{
		for (unsigned int i = 0; i < pressedKeys.size(); i++)
		{
			if (pressedKeys[i] == key)
				return true;
		}

		return false;
	}

	bool IsKeyDown(Key key)
	{
		for (unsigned int i = 0; i < downKeys.size(); i++)
		{
			if (downKeys[i] == key)
				return true;
		}

		return false;
	}

	bool IsKeyUp(Key key)
	{
		//std::cout << key;
		for (unsigned int i = 0; i < upKeys.size(); i++)
		{
			if (upKeys[i] == key)
				return true;
		}

		return false;
	}

	bool IsKeyReleased(Key key)
	{
		for (unsigned int i = 0; i < releasedKeys.size(); i++)
		{
			if (releasedKeys[i] == key)
				return true;
		}

		return false;
	}

} }