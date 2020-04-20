#pragma once
#include <glm\glm.hpp>
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

			}
		};
	}
}