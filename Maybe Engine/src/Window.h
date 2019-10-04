#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/Core.h"
#include "events/EventQueue.h"
#include "events/WindowEvents.h"
#include "events/KeyEvents.h"
#include "events/MouseEvents.h"

namespace mb {

	class Window
	{
	public:
		struct WindowData {
			unsigned int width;
			unsigned int height;
			char* title;
			bool VSync;

			WindowData(unsigned int width, unsigned int height, const char* title, bool VSync=false)
			{
				this->width = width;
				this->height = height;
				this->title = (char*) title;
				this->VSync = VSync;
			}
		};
	public:
		Window(const WindowData& data);
		~Window();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.width; }
		inline unsigned int GetHeight() const { return m_Data.height; }

		inline Vec2 GetSize() const { return Vec2((float) m_Data.width, (float) m_Data.height); }

		void SetVSync(bool VSync);
		inline bool IsVSync() const { return m_Data.VSync; }
		
		inline GLFWwindow* GetGLFWwindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
		
		static bool s_GLFWInitialized;
		static bool s_GLEWInitialized;
	};

}