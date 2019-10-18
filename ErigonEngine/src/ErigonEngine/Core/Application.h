#pragma once

#include "Core.h"
#include "Window.h"
#include "ErigonEngine/Core/Timestep.h"
#include "ErigonEngine/Layers/LayerStack.h"
#include "ErigonEngine/Events/Event.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/ImGUI/ImGUILayer.h"
#include "ErigonEngine/Renderer/Shader.h"
#include "ErigonEngine/Renderer/VertexBuffer.h"
#include "ErigonEngine/Renderer/IndexBuffer.h"
#include "ErigonEngine/Renderer/VertexArray.h"
#include "ErigonEngine/Renderer/OrtographicCamera.h"

namespace ErigonEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline IWindow& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		Scope<IWindow> m_Window;
		ImGUILayer*  m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}