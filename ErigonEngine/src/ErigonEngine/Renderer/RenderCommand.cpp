#include "eepch.h"
#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace ErigonEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}