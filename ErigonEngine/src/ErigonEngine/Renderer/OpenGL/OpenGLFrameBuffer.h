#pragma once
#include "ErigonEngine\Renderer\FrameBuffer.h"
namespace ErigonEngine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer();

		virtual ~OpenGLFrameBuffer();

		virtual void Bind(uint32 textureId, uint32 width, uint32 height) const override;
		virtual void Unbind() const override;
	private:
		uint32 m_RendererID;
	};
}