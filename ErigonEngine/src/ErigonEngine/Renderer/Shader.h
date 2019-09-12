#pragma once
#include <string>
#include <ErigonEngine/Core/Types.h>
#include <glm/glm.hpp>

namespace ErigonEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* Create(const std::string& filePath);
	protected:
		uint32 m_RendererID;
	};
}