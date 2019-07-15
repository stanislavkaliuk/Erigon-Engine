#pragma once

#include "Core.h"
#include "Window.h"
#include "ErigonEngine/Layers/LayerStack.h"
#include "ErigonEngine/Events/Event.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/ImGUI/ImGUILayer.h"
#include "ErigonEngine/Renderer/Shader.h"
#include "ErigonEngine/Renderer/Buffer.h"

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
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}