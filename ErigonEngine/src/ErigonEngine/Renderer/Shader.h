#pragma once
#include <string>
#include <glm/glm.hpp>
#include "ErigonEngine/Core/Types.h"

namespace ErigonEngine
{
	class Shader
	{
	protected:
		int32 m_RendererID;
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}