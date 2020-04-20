#pragma once
#include "IGameObject.h"
#include <EECS_Controller.hpp>

namespace ErigonEngine
{
	template <class T>
	class GameObject : public IGameObject
	{

	private:
		::ECS::Entity connectedEntity;
	};
}