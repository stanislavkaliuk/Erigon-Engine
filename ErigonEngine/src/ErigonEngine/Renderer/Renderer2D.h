#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrtographicCamera.h"
#include "Texture.h"

namespace ErigonEngine
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Destroy();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Draw(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color);
		static void Draw(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		static void Draw(const glm::vec2& position, const glm::vec3& size, const Ref<Texture2D>& texture);
		static void Draw(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}