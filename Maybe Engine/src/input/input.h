#pragma once

#include <vector>
//#include <GLFW\glfw3.h>

#include "..\graphics\Window.h"

namespace mb { namespace input {

	enum Key 
	{
		Q_KEY = GLFW_KEY_Q,
		W_KEY = GLFW_KEY_W,
		E_KEY = GLFW_KEY_E,
		R_KEY = GLFW_KEY_R,
		T_KEY = GLFW_KEY_T,
		Y_KEY = GLFW_KEY_Y,
		U_KEY = GLFW_KEY_U,
		I_KEY = GLFW_KEY_I,
		O_KEY = GLFW_KEY_O,
		P_KEY = GLFW_KEY_P,
		A_KEY = GLFW_KEY_A,
		S_KEY = GLFW_KEY_S,
		D_KEY = GLFW_KEY_D,
		F_KEY = GLFW_KEY_F,
		G_KEY = GLFW_KEY_G,
		H_KEY = GLFW_KEY_H,
		J_KEY = GLFW_KEY_J,
		K_KEY = GLFW_KEY_K,
		L_KEY = GLFW_KEY_L,
		Z_KEY = GLFW_KEY_Z,
		X_KEY = GLFW_KEY_X,
		C_KEY = GLFW_KEY_C,
		V_KEY = GLFW_KEY_V,
		B_KEY = GLFW_KEY_B,
		N_KEY = GLFW_KEY_N,
		M_KEY = GLFW_KEY_M,
		UP_KEY = GLFW_KEY_UP,
		DOWN_KEY = GLFW_KEY_DOWN,
		LEFT_KEY = GLFW_KEY_LEFT,
		RIGHT_KEY = GLFW_KEY_RIGHT,
		SPACE_KEY = GLFW_KEY_SPACE
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