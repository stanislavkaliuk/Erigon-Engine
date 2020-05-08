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
#include "ErigonEngine/ECS/ECSController.h"
#include "ErigonEngine/MemoryManager/MemoryManager.h"
#include "ErigonEngine/FileSystem/Content.h"

namespace ErigonEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
		void Run();
		void OnEvent(const Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
		inline IWindow& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline ECSController& GetECSController() { return *m_ECS_System; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnAppWantExit(const AppExitEvent& e);
	private:
		Scope<ECSController> m_ECS_System;
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