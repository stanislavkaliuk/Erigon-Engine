#include "eepch.h"
#include "Shader.h"
#include "Renderer2D.h"

#include "ErigonEngine/Renderer/OpenGL/OpenGLShader.h"

namespace ErigonEngine
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None:
			default:
				EE_CORE_ASSERT(false, "RenderAPI is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}
	
	}

	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer2D::GetAPI())
		{
			case RendererAPI::API::None:
			default:
				EE_CORE_ASSERT(false, "RenderAPI is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(filePath);
		}
	
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		EE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		EE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}