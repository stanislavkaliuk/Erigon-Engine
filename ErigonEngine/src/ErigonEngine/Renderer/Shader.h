#pragma once
#include <string>
#include <ErigonEngine/Core/Types.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace ErigonEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Ref<Shader> Create(const std::string& filePath);
	protected:
		uint32 m_RendererID;
	};

	class ShaderLibrary
	{

	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader>Load(const std::string& filepath);
		Ref<Shader>Load(const std::string& name, const std::string & filePath);
		Ref<Shader>Get(const std::string& name);
		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}