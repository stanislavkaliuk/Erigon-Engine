#include "eepch.h"
#include "GameObject.h"

namespace ErigonEngine
{
	GameObject::GameObject(::ECS::Entity entity, std::initializer_list<std::any> components) : connectedEntity(entity), connectedComponents(components)
	{
		
	}
}
