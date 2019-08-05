#pragma once
#include "ErigonEngine/Core/Types.h"
#include "ErigonEngine/Renderer/VertexBuffer.h"
#include "ErigonEngine/Renderer/IndexBuffer.h"

namespace ErigonEngine
{
	class D3DVertexBuffer : public VertexBuffer
	{
		public:
		D3DVertexBuffer(float* vertices, uint32 size);
		virtual ~D3DVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		uint32 m_RendererID;
		BufferLayout m_Layout;
	};
}