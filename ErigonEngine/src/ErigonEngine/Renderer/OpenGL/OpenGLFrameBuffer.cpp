#include "eepch.h"
#include "OpenGLFrameBuffer.h"
#include <glad\glad.h>

namespace ErigonEngine
{
	OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
		glGenFramebuffers(1, &m_RendererID);
		glGenRenderbuffers(1, &m_RenderBuffID);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFrameBuffer::Bind(uint32 textureId, uint32 width, uint32 height) const
	{
		glViewport(0, 0, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}