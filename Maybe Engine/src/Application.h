#pragma once

#include <memory>
#include <functional>

#include "core/Core.h"
#include "core/List.h"
#include "core/Time.h"
#include "events/EventQueue.h"
#include "graphics/RenderCommand.h"
#include "Window.h"
#include "LayerStack.h"

namespace mb {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event* e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		inline static Application* GetInstance() { return s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }
	protected:
		void SetCloseOnEscape(bool close);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
		bool m_CloseOnEscape;

		static Application* s_Instance;
	protected:
		LayerStack m_LayerStack;
	};

}