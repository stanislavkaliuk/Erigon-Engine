#pragma once

#include "Core.h"
#include "Window.h"
#include "ErigonEngine/Layers/LayerStack.h"
#include "ErigonEngine/Events/Event.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/ImGUI/ImGUILayer.h"
#include "ErigonEngine/Renderer/Shader.h"
#include "ErigonEngine/Renderer/VertexBuffer.h"
#include "ErigonEngine/Renderer/IndexBuffer.h"
#include "ErigonEngine/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_ShaderBlue;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_Square;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}