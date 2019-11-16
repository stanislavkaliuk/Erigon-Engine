#include "eepch.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>

namespace ErigonEngine
{
	static GLenum StringToShaderType(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string source = ReadFile(filePath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind('.');
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filePath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			EE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeLength + 1;
			std::string type = source.substr(begin, eol - begin);
			EE_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shaderType specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			EE_CORE_ASSERT(nextLinePos != std::string::npos, "Shader syntax error!");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[StringToShaderType(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		m_RendererID = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSources.size());
		for (auto& mapItem : shaderSources)
		{
			GLenum type = mapItem.first;
			const std::string& source = mapItem.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);
				EE_CORE_ERROR("{0}", infoLog.data());
				EE_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}
			glAttachShader(m_RendererID, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(m_RendererID);
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			EE_CORE_ERROR("{0}", infoLog.data());
			EE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		for (auto id : glShaderIDs)
			glDetachShader(m_RendererID, id);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			EE_CORE_ERROR("Could not open shader file '{0}'", filePath);
		}
		return result;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& val)
	{
		UploadUniformMat4(name, val);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& val)
	{
		UploadUniformF4(name, val);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& val)
	{
		UploadUniformF3(name, val);
	}

	void OpenGLShader::SetInt(const std::string& name, const int val)
	{
		UploadUniformI(name, val);
	}

	void OpenGLShader::UploadUniformI(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformF(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformF2(const std::string& name, const glm::vec2& float2Array)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(float2Array));
	}

	void OpenGLShader::UploadUniformF3(const std::string& name, const glm::vec3& float3Array)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(float3Array));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformF4(const std::string& name, const glm::vec4& float4Array)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(float4Array));
	}
}


