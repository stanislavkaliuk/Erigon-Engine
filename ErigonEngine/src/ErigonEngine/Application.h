#pragma once

#include "Core.h"
#include "Window.h"
#include "ErigonEngine/LayerStack.h"
#include "ErigonEngine/Events/Event.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/ImGUI/ImGUILayer.h"

namespace ErigonEngine
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline IWindow& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		std::unique_ptr<IWindow> m_Window;
		ImGUILayer*  m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClosed(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}