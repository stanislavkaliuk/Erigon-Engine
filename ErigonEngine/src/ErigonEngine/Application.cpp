#include "eepch.h"
#include "Application.h"
#include "ErigonEngine/Log.h"
#include <GLFW/glfw3.h>

namespace ErigonEngine
{

#define BIND_EVENT(x) std::bind(&x, this,std::placeholders::_1)
	Application::Application()
	{

		m_Window = std::unique_ptr<IWindow>(IWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClosed));
		EE_CORE_INFO(e.ToString());
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
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