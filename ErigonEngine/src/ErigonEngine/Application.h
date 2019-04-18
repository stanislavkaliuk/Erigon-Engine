#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "Window.h"

namespace ErigonEngine
{
	class ERIGON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		std::unique_ptr<IWindow> m_Window;
		bool m_Running = true;
		bool OnWindowClosed(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}