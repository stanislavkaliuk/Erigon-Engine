#pragma once

#include "ErigonEngine/Renderer/Shader.h"

typedef unsigned int GLenum;
namespace ErigonEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& filePath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetMat4(const std::string& name, const glm::mat4& val) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& val) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& val) override;
		virtual void SetInt(const std::string& name, const int val) override;

		void UploadUniformI(const std::string& name, int value);

		void UploadUniformF(const std::string& name, float value);
		void UploadUniformF2(const std::string& name, const glm::vec2& float2Array);
		void UploadUniformF3(const std::string& name, const glm::vec3& float3Array);
		void UploadUniformF4(const std::string& name, const glm::vec4& float4Array);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string ReadFile(const std::string& filePath);

	private:
		uint32 m_RendererId;
		std::string m_Name;
	};
}