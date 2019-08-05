#include "eepch.h"
#include "WinWindow.h"
#include "ErigonEngine/Renderer/DX11/D3DContext.h"

namespace ErigonEngine
{
	static void D3DErrorCallback(int error, const char* description)
	{
		EE_CORE_ERROR("D3D Error {0} : {1} ", error, description);
	}

	IWindow* IWindow::Create(const WindowProps& props)
	{
		return new WinWindow(props);
	}

	WinWindow::WinWindow(const WindowProps& props)
	{
		Init(props);
	}

	WinWindow::~WinWindow()
	{
		Shutdown();
	}

	void WinWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EE_CORE_INFO("Creating window {0} ({1},{2})", props.Title, props.Width, props.Height);

		std::wstring title = std::wstring(m_Data.Title.begin(), m_Data.Title.end());
		HWND window = CreateWindow(L"ErigonEngine", title.c_str(), WS_VISIBLE, 0, 0, m_Data.Width, m_Data.Height, NULL, NULL, NULL, NULL);
		m_Window = &window;
		m_Context = new D3DContext(*m_Window);
		m_Context->Init();
		SetVSync(true);

		//set glfw callback
		/*
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow * window, int width, int height)
		{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow * window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window, int button, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow * window, double x, double y) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow * window, double x, double y) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});*/
	}

	void WinWindow::Shutdown()
	{
		//glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		//glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WinWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			//glfwSwapInterval(1);
		}
		else
		{
			//glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}