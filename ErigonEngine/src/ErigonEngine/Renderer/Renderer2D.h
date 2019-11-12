#pragma once

#include "OrtographicCamera.h"

namespace ErigonEngine
{
	class Renderer2D
	{
		static void Init();
		static void Destroy();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		//static void DrawSprite(const Transform& transform, const glm::vec4& color);
	};
}