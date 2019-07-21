#include "eepch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace ErigonEngine
{
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vsource = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vsource, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);
			EE_CORE_ERROR("{0}", infoLog.data());
			EE_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* fsource = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fsource, 0);

		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			EE_CORE_ERROR("{0}", infoLog.data());
			EE_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			EE_CORE_ERROR("{0}", infoLog.data());
			EE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}