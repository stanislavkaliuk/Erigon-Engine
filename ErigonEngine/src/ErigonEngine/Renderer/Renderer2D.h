#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include <glm\glm.hpp>

namespace ErigonEngine
{
	struct DrawCallData
	{
		glm::mat4 transform;
		glm::mat4 viewProjection;

		Ref<Texture2D> texture;
		glm::vec4 color;

		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Destroy();
		static void BeginSnap();
		static void EndSnap();
		static uint32 GetSnap();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void RecreateFramebuffer(uint32_t width, uint32_t heigth);
		static void Draw(DrawCallData drawCallDataCollection);
		static glm::vec2 GetFrameBufferSize();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}