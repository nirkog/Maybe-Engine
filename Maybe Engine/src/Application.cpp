#include "Application.h"

namespace mb {

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Running(true), m_CloseOnEscape(false)
	{
		ASSERT(!s_Instance, "Application already exists");

		s_Instance = this;

		m_Window = std::make_unique<Window>(Window::WindowData(1200, 800, "Maybe Reloaded!"));
	}

	void Application::Run()
	{
		//std::chrono::time_point start = s
		std::chrono::time_point old = std::chrono::high_resolution_clock::now();
		std::chrono::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> delta = now - old;

		while (m_Running)
		{
			now = std::chrono::high_resolution_clock::now();
			delta = now - old;
			old = std::chrono::high_resolution_clock::now();

			for (List<Layer*>::Iterator it = m_LayerStack.Begin(), end = m_LayerStack.End(); it != end; it++)
				(*it)->OnUpdate(delta.count());

			while (EventQueue::Count() > 0)
				this->OnEvent(EventQueue::Pop());

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event* e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		if (m_CloseOnEscape && e->GetType() == EventType::KeyPressedEvent && ((KeyPressedEvent&) (*e)).GetKeyCode() == KeyCode::KEY_ESCAPE)
			m_Running = false;

		for (List<Layer*>::Iterator it = m_LayerStack.Begin(), end = m_LayerStack.End(); it != end; it++)
		{
			if (e->Handled) break;

			(*it)->OnEvent(static_cast<Event&>(*e));
		}

		delete e;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::SetCloseOnEscape(bool close)
	{
		m_CloseOnEscape = close;
	}

}