#pragma once
#include "Transform.h"

template<class T>
class GameObject : public Erigon::ECS::Entity<T>
{
public:
	GameObject()
	{
		AddComponent<Transform>(Transform());
	}
};