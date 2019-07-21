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
			{ 
				EE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}
		EE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}


