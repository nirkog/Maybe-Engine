#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "..\maths\vec2.h"

namespace mb { namespace graphics {
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		bool Open() const;
		void Close() const;
		void Clear(float r, float g, float b, float a) const;
		void Update();

		void QuitOnPress(unsigned int key);
		void DisableQuitOnPress();

		void SetTitle(const char* title);

		inline const GLFWwindow* GetGLFWwindow() const { return m_Window; }

		inline void Destroy() { glfwDestroyWindow(m_Window); }
	private:
		//void OnResize(GLFWwindow* window, int width, int height);
	private:
		char* m_Title;
		maths::Vec2 m_Size;
		GLFWwindow* m_Window;

		bool m_QuitOnPress;
		unsigned int m_QuitKey;
	};
} }