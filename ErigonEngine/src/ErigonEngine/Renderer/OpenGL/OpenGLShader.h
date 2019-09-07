#pragma once

#include "ErigonEngine/Renderer/Shader.h"

namespace ErigonEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformI(const std::string& name, int value);

		void UploadUniformF(const std::string& name, float value);
		void UploadUniformF2(const std::string& name, const glm::vec2& float2Array);
		void UploadUniformF3(const std::string& name, const glm::vec3& float3Array);
		void UploadUniformF4(const std::string& name, const glm::vec4& float4Array);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}