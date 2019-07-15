#pragma once

#include "ErigonEngine/Renderer/VertexBuffer.h"
#include "ErigonEngine/Renderer/IndexBuffer.h"

namespace ErigonEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual uint32_t GetCount() const override { return m_Count; }
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}