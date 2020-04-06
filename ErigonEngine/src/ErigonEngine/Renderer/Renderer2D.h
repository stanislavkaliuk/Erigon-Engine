#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrtographicCamera.h"
#include "Texture.h"
#include <glm\glm.hpp>

namespace ErigonEngine
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Destroy();
		static void BeginSnap(uint32 width, uint32 height);
		static void EndSnap();
		static uint32 GetSnap();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void RecreateFramebuffer(uint32_t width, uint32_t heigth);
		static void Draw(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color);
		static void Draw(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		static void Draw(const glm::vec2& position, const glm::vec3& size, const Ref<Texture2D>& texture);
		static void Draw(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture);
		static void Draw(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, const glm::vec4& color);
		static void Draw(const glm::vec2& position, const glm::vec3& size, const Ref<Texture2D>& texture, const glm::vec4& color);
		static glm::vec2 GetFrameBufferSize();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}