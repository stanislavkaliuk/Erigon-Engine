#include "eepch.h"
#include "Renderer2D.h"
#include "FrameBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ErigonEngine
{
	struct RenderData
	{
		Ref<VertexArray> squareVA;
		Ref<Shader> shader;
		Ref<Texture> frameBufferTexture;
		Ref<FrameBuffer> frameBuffer;
	};
	static Ref<Texture2D> WhiteTexture;
	static RenderData data;

	void Renderer2D::Init()
	{
		RenderCommand::Init();
		data = RenderData();

		data.squareVA = VertexArray::Create();

		float squareVert[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVert, sizeof(squareVert));
		squareVB->SetLayout
		({	
			{ShaderDataType::Float3, "a_Position"}, 
			{ShaderDataType::Float2, "a_TexCoord"} 
		});

		data.squareVA->AddVertexBuffer(squareVB);

		uint32_t sqIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(sqIndicies, sizeof(sqIndicies));
		
		data.squareVA->SetIndexBuffer(squareIB);

		WhiteTexture = Texture2D::Create();
		
		RecreateFramebuffer(1280, 720);

		data.shader = Shader::Create("assets/shaders/Sprite.egl");
	}

	void Renderer2D::Destroy()
	{
		data.frameBufferTexture->~Texture();
		data.frameBuffer->~FrameBuffer();
		data.squareVA->~VertexArray();
		data.shader->~Shader();

		data.frameBufferTexture.reset();
		data.frameBuffer.reset();
		data.squareVA.reset();
		data.shader.reset();
	}

	void Renderer2D::BeginSnap(uint32 width, uint32 height)
	{
		uint32 textureID = data.frameBufferTexture->GetTextureId();
		data.frameBuffer->Bind(textureID, width, height);
	}

	void Renderer2D::EndSnap()
	{
		data.frameBuffer->Unbind();
	}

	uint32 Renderer2D::GetSnap()
	{
		return data.frameBufferTexture->GetTextureId();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data.shader->Bind();
		data.shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
	{
		//RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer2D::RecreateFramebuffer(uint32_t width, uint32_t heigth)
	{
		data.frameBufferTexture.reset();
		data.frameBuffer.reset();
		RenderCommand::SetViewport(0, 0, width, heigth);
		data.frameBuffer = FrameBuffer::Create();
		data.frameBufferTexture = Texture2D::Create(width, heigth);
	}

	void Renderer2D::Draw(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color)
	{
		Draw(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::Draw(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
		data.shader->SetFloat4("u_Color", color);
		WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shader->SetMat4("u_Transform", transform);
		
		data.squareVA->Bind();
		RenderCommand::DrawIndexed(data.squareVA);
	}

	void Renderer2D::Draw(const glm::vec2& position, const glm::vec3& size, const Ref<Texture2D>& texture)
	{
		Draw(glm::vec3(position, 0.0f), size, texture);
	}

	void Renderer2D::Draw(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture)
	{
		data.shader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shader->SetMat4("u_Transform", transform);
		
		data.squareVA->Bind();
		RenderCommand::DrawIndexed(data.squareVA);
	}

	void Renderer2D::Draw(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		data.shader->SetFloat4("u_Color", color);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shader->SetMat4("u_Transform", transform);

		data.squareVA->Bind();
		RenderCommand::DrawIndexed(data.squareVA);
	}

	void Renderer2D::Draw(const glm::vec2& position, const glm::vec3& size, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		Draw(glm::vec3(position, 1.0f), size, texture, color);
	}
}