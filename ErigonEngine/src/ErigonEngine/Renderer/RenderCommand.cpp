#include "eepch.h"
#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace ErigonEngine
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}