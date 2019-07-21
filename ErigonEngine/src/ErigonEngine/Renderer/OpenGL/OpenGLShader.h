#pragma once
#include "ErigonEngine/Renderer/Shader.h"

namespace ErigonEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) override;
	};
}