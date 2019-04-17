#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace ErigonEngine
{
	class ERIGON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<IWindow> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}