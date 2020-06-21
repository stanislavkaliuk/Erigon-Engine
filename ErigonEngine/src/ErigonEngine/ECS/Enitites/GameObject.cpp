#include "eepch.h"
#include "GameObject.h"

namespace ErigonEngine
{
	GameObject::GameObject(::ECS::Entity entity, ::ECS::Signature objectSignature, std::initializer_list<std::any> components) : connectedEntity(entity), connectedComponents(components), signature(objectSignature)
	{
	}
}
