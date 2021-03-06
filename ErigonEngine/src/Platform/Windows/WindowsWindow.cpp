#include "eepch.h"
#include "WindowsWindow.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/Events/KeyEvent.h"
#include "ErigonEngine/Events/MouseEvent.h"
#include "ErigonEngine/Renderer/OpenGL/OpenGLContext.h"


namespace ErigonEngine
{
	static bool s_GLFWInitialized = false;


	static void GLFWErrorCallback(int error, const char* description)
	{
		EE_CORE_ERROR("GLFW Error {0} : {1} ", error, description);
	}

	IWindow* IWindow::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = 1920;
		m_Data.Height = 1080;

		EE_CORE_INFO("Creating window {0} ({1},{2})", props.Title, 1920, 1080);


		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			EE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(1920, 1080, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = CreateScope<OpenGLContext>(m_Window);
		m_Context->Init();
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		//set glfw callback

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
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}