#include "eepch.h"
#include "OpenGLContext.h"

namespace ErigonEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		EE_CORE_ASSERT(windowHandle, "Window handler is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EE_CORE_ASSERT(status, "Failed to initialize Glad!");
		EE_CORE_INFO("OpenGL Info:");
		EE_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		EE_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		EE_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}