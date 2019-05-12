#pragma once

#include "GL.h"
#include "Color.h"

#include "..\maths\maths.h"

namespace mb { namespace graphics {
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		bool Open() const;
		void Close() const;
		void Clear(float r, float g, float b, float a) const;
		void Clear(Color color) const;
		void Clear() const;
		void Update();

		void QuitOnPress(unsigned int key);
		void DisableQuitOnPress();

		void SetTitle(const char* title);
		void SetVsync(const bool state);

		void SetClearColor(Color color) { m_ClearColor = color; }
		void SetClearColor(const char* hex) { m_ClearColor = { hex }; }
		void SetClearColor(const float& r, const float& g, const float& b, const float& a) { m_ClearColor = { r, g, b, a }; }

		inline const GLFWwindow* GetGLFWwindow() const { return m_Window; }
		inline const maths::Vec2 GetSize() const { return m_Size; }

		inline void Destroy() { glfwDestroyWindow(m_Window);}
	private:
		//void OnResize(GLFWwindow* window, int width, int height);
	private:
		char* m_Title;
		maths::Vec2 m_Size;
		GLFWwindow* m_Window;

		Color m_ClearColor;

		bool m_QuitOnPress;
		unsigned int m_QuitKey;

		static unsigned int m_OpenWindows;
	};
} }