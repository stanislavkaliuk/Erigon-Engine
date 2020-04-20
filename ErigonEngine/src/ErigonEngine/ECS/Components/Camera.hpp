#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ErigonEngine
{
	namespace ECS
	{
		struct Camera
		{
			float nearClipPlane = 0.0f;
			float farClipPlaner = 50.0f;

			glm::mat4 viewProjectionMatrix;

			void RecalculateProjectionMatrix(glm::vec2 renderViewSize)
			{
				projectionMatrix = glm::ortho(0.0f, renderViewSize.x, renderViewSize.y, 0.0f, nearClipPlane, farClipPlaner);
				viewProjectionMatrix = projectionMatrix * viewMatrix;
			}

			void RecalculatViewMatrix(glm::vec3 position)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
				viewMatrix = glm::inverse(transform);
				viewProjectionMatrix = projectionMatrix * viewMatrix;
			}
		private:
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};
	}
}