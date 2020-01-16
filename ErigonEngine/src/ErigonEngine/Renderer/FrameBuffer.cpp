#include "eepch.h"
#include "FrameBuffer.h"
#include "Renderer2D.h"
#include "OpenGL\OpenGLFrameBuffer.h"

namespace ErigonEngine
{
	Ref<FrameBuffer> ErigonEngine::FrameBuffer::Create()
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLFrameBuffer>();
		}
	}
}