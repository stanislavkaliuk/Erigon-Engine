#include "eepch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace ErigonEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ErigonEngine::ShaderDataType::Float:  return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float2: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float3: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float4: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Mat3:   return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Mat4:   return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Int:	   return GL_INT;
			case ErigonEngine::ShaderDataType::Int2:   return GL_INT;
			case ErigonEngine::ShaderDataType::Int3:   return GL_INT;
			case ErigonEngine::ShaderDataType::Int4:   return GL_INT;
			case ErigonEngine::ShaderDataType::Bool:   return GL_BOOL;
		}

		EE_CORE_ERROR("Unknown shader data type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		EE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)((size_t)element.Offset));
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}