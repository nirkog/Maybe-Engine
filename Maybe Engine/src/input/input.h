#pragma once

#include <vector>
//#include <GLFW\glfw3.h>

#include "..\graphics\Window.h"

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

	class Input 
	{
	public:
		static void Init();
		static void Update(const graphics::Window& window);

		static bool IsKeyPressed(Key key);
		static bool IsKeyDown(Key key);
		static bool IsKeyReleased(Key key);
		static bool IsKeyUp(Key key);
	private:
		static Key keys[];
		static unsigned int keyCout;
		static std::vector<Key> upKeys, downKeys, pressedKeys, releasedKeys;
	};

} }