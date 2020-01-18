#pragma once
#include "ErigonEngine/ECS/IGameObject.h"
#include <vector>

namespace ErigonEngine
{
	class Scene
	{
	public:
		std::vector<IGameObject*> gameObjects;
	};
}