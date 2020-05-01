#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/packing.hpp>
namespace ErigonEngine
{
	namespace ECS
	{
		struct Transform
		{
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			glm::mat4 GetTransformMatrix()
			{
				return glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);
			}
		};
	}
}