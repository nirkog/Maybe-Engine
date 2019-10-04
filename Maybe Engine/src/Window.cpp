#include "Window.h"

namespace mb {

	bool Window::s_GLFWInitialized = false;
	bool Window::s_GLEWInitialized = false;

	Window::Window(const WindowData& data)
		: m_Data(data)
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ASSERT(success, "Could not initialize GLFW!");
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title, NULL, NULL);

		ASSERT(m_Window != NULL, "Could not initialize window!");

		glfwMakeContextCurrent(m_Window);

		if (!s_GLEWInitialized)
		{
			GLenum success = glewInit();
			ASSERT(success == GLEW_OK, "Could not initialize GLEW!");
			s_GLEWInitialized = true;
		}

		glfwSetWindowUserPointer(m_Window, (void*) &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			EventQueue::PushEvent(new WindowCloseEvent());
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

			data->width = (unsigned int) width;
			data->height = (unsigned int) height;

			EventQueue::PushEvent(new WindowResizeEvent(data->width, data->height));
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
				EventQueue::PushEvent(new KeyPressedEvent(keyCode, mods, (action == GLFW_PRESS) ? false : true));
			else if (action == GLFW_RELEASE)
				EventQueue::PushEvent(new KeyReleasedEvent(keyCode, mods));
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codePoint) {
			EventQueue::PushEvent(new KeyTypedEvent(codePoint));
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS)
				EventQueue::PushEvent(new MouseButtonPressedEvent(button));
			else if (action == GLFW_RELEASE)
				EventQueue::PushEvent(new MouseButtonReleasedEvent(button));
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			EventQueue::PushEvent(new MouseScrolledEvent((float) xOffset, (float) yOffset));
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			EventQueue::PushEvent(new MouseMovedEvent((float) x, (float) y));
		});

		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow*, int entered) {
			if (entered == GLFW_TRUE) EventQueue::PushEvent(new MouseEnterEvent());
			else if (entered == GLFW_FALSE) EventQueue::PushEvent(new MouseLeaveEvent());
		});

		SetVSync(m_Data.VSync);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);

		/*
		
		RELOCATE
		
		*/
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool VSync)
	{
		if (VSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = VSync;
	}

}