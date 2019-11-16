#include "eepch.h"
#include "Application.h"
#include "ErigonEngine/Log/Log.h"
#include "ErigonEngine/Input/Input.h"
#include "ErigonEngine/Renderer/Renderer2D.h"
#include <GLFW/glfw3.h>

namespace ErigonEngine
{

#define BIND_EVENT(x) std::bind(&x, this,std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	
	Application::Application() 
	{
		EE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Scope<IWindow>(IWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		Renderer2D::Init();

		m_ImGuiLayer = new ImGUILayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResized));
		//EE_CORE_INFO(e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		m_Minimized = e.GetWidth() == 0 || e.GetHeight() == 0;
		Renderer2D::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = Timestep(time, time - m_LastFrameTime);
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();
			for (Layer* layer : m_LayerStack)
					layer->OnPostUpdate(timestep);

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}