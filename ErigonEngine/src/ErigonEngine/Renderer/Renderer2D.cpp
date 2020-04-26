#include "eepch.h"
#include "Renderer2D.h"
#include "FrameBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ErigonEngine
{
	struct FrameBufferData
	{
		Ref<Texture> frameBufferTexture;
		Ref<FrameBuffer> frameBuffer;
		glm::vec2 framebufferSize;
	};

	static Ref<Texture2D> WhiteTexture;
	static FrameBufferData frameBufferData;

	void Renderer2D::Init()
	{
		RenderCommand::Init();
		frameBufferData = FrameBufferData();

		WhiteTexture = Texture2D::Create();
		frameBufferData.framebufferSize = glm::vec2(1280, 720);
		RecreateFramebuffer(frameBufferData.framebufferSize.x, frameBufferData.framebufferSize.y);
	}

	void Renderer2D::Destroy()
	{
		frameBufferData.frameBufferTexture->~Texture();
		frameBufferData.frameBuffer->~FrameBuffer();

		frameBufferData.frameBufferTexture.reset();
		frameBufferData.frameBuffer.reset();
	}

	glm::vec2 Renderer2D::GetFrameBufferSize()
	{
		return { frameBufferData.framebufferSize.x, frameBufferData.framebufferSize.y };
	}

	void Renderer2D::BeginSnap()
	{
		uint32 textureID = frameBufferData.frameBufferTexture->GetTextureId();
		glm::vec2 size = GetFrameBufferSize();
		frameBufferData.frameBuffer->Bind(textureID, size.x, size.y);
	}

	void Renderer2D::EndSnap()
	{
		frameBufferData.frameBuffer->Unbind();
	}

	uint32 Renderer2D::GetSnap()
	{
		return frameBufferData.frameBufferTexture->GetTextureId();
	}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
	{
		//RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer2D::RecreateFramebuffer(uint32_t width, uint32_t height)
	{
		frameBufferData.frameBufferTexture.reset();
		frameBufferData.frameBuffer.reset();
		RenderCommand::SetViewport(0, 0, width, height);
		frameBufferData.frameBuffer = FrameBuffer::Create();
		frameBufferData.frameBufferTexture = Texture2D::Create(width, height);
		frameBufferData.framebufferSize = glm::vec2(width, height);
	}

	void Renderer2D::Draw(DrawCallData drawCallDataCollection)
	{
		drawCallDataCollection.shader->Bind();
		drawCallDataCollection.shader->SetMat4("u_ViewProjection", drawCallDataCollection.viewProjection);
		drawCallDataCollection.shader->SetFloat4("u_Color", drawCallDataCollection.color);
		
		if (drawCallDataCollection.texture != nullptr)
		{
			drawCallDataCollection.texture->Bind();
		}
		else
		{
			WhiteTexture->Bind();
		}

		drawCallDataCollection.shader->SetMat4("u_Transform", drawCallDataCollection.transform);
		drawCallDataCollection.vertexArray->Bind();
		RenderCommand::DrawIndexed(drawCallDataCollection.vertexArray);
	}
}