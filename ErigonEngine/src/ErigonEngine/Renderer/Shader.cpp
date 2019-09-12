#include "eepch.h"
#include "Shader.h"
#include "Renderer.h"

#include "ErigonEngine/Renderer/OpenGL/OpenGLShader.h"

namespace ErigonEngine
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			default:
				EE_CORE_ASSERT(false, "RenderAPI is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSource, fragmentSource);
		}
	
	}

	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			default:
				EE_CORE_ASSERT(false, "RenderAPI is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(filePath);
		}
	
	}
}