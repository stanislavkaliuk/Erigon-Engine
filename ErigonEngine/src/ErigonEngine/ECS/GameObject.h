#pragma once
#include "Transform.h"

using GameObjectId = Erigon::ECS::EntityID;
using GameObjectTypeId = Erigon::ECS::EntityTypeID;

template<class T>
class GameObject : public Erigon::ECS::Entity<T>
{
public:
	GameObject()
	{
		AddComponent<Transform>(Transform());
	}
	virtual void Update() = 0;
};