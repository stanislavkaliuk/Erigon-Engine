#include "eepch.h"
#include "Application.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/Log.h"
#include <GLFW/glfw3.h>

namespace ErigonEngine
{


	Application::Application()
	{

		m_Window = std::unique_ptr<IWindow>(IWindow::Create());

	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}