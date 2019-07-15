#include "eepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace ErigonEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}