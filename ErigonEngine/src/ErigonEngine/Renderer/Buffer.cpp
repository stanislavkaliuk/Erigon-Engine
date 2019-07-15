#include "eepch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace ErigonEngine
{
	VertexBuffer* ErigonEngine::VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	IndexBuffer* ErigonEngine::IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

