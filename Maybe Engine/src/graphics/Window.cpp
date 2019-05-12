#include "window.h"

namespace mb { namespace graphics { 

	unsigned int Window::m_OpenWindows = 0;

	void OnResize(GLFWwindow* window, int width, int height)
	{
		GLCall(glViewport(0, 0, width, height));
	}

	Window::Window(unsigned int width, unsigned int height, const char* title)
		: m_Size((float) width, (float) height), m_Title((char*) title), m_QuitOnPress(false), m_QuitKey(0)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (m_Window == NULL)
		{
			std::cout << "FATAL ERROR: can't create a window!" << std::endl;
		}

		glfwSetFramebufferSizeCallback(m_Window, mb::graphics::OnResize);

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
			std::cout << "NOT OK"; 

		glfwSwapInterval(0);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	Window::~Window()
	{
		m_OpenWindows--;
		if (m_OpenWindows == 0)
		{
			Destroy();
			glfwTerminate();
		}
	}

	bool Window::Open() const 
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::Close() const
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	
	void Window::Clear(float r, float g, float b, float a) const
	{
		GLCall(glClearColor(r, g, b, a));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::Clear(maths::Vec4 color) const
	{
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::Clear() const
	{
		GLCall(glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::Update()
	{
		if (m_QuitOnPress)
		{
			if (glfwGetKey(m_Window, m_QuitKey) == GLFW_PRESS)
				Close();
		}

		int x, y;
		glfwGetFramebufferSize(m_Window, &x, &y);
		m_Size = { (float) x, (float) y };

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::QuitOnPress(unsigned int key)
	{
		if (!m_QuitOnPress)
			m_QuitOnPress = true;

		m_QuitKey = key;
	}

	void Window::DisableQuitOnPress()
	{
		m_QuitOnPress = false;
	}

	void Window::SetTitle(const char* title)
	{
		m_Title = (char*) title;
		glfwSetWindowTitle(m_Window, title);
	}
	
	void Window::SetVsync(const bool state)
	{
		glfwSwapInterval(state);
	}

} }