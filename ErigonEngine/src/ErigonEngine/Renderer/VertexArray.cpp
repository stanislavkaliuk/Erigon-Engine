#include "eepch.h"
#include "VertexArray.h"
#include "Renderer2D.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace ErigonEngine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}