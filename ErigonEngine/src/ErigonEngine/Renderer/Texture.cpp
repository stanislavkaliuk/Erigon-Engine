#include "eepch.h"
#include "Texture.h"
#include "Renderer2D.h"
#include "OpenGL/OpenGLTexture.h"
namespace ErigonEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create()
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None: 
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>();
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}