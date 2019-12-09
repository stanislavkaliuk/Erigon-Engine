#pragma once

#include <CommCtrl.h>
#include "ErigonEngine/Core/Window.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "ErigonEngine/Renderer/GraphicsContext.h"

namespace ErigonEngine
{
	class WindowsWindow : public IWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	
		enum MenuBarIDs
		{
			FILE_MENU_NEW = 1 << 0,
			FILE_MENU_OPEN = 2 << 0,
			FILE_MENU_EXIT = 3 << 0
		};

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		virtual void SetupMenuBar();
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			EventCallback EventCallback;
			bool VSync;
		};

		WindowData m_Data;


	};
}