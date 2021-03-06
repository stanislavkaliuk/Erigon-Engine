#include "eepch.h"
#include "Buffer.h"
#include "RendererAPI.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace ErigonEngine
{
	Ref<VertexBuffer> ErigonEngine::VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> ErigonEngine::IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

