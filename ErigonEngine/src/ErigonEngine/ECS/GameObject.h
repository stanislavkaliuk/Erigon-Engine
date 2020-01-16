#pragma once
#include "IGameObject.h"
#include <EECS.h>
#include "Transform.h"

using namespace Erigon::ECS;

namespace ErigonEngine
{
	using GameObjectId = EntityID;
	using GameObjectTypeId = EntityTypeID;

	template <class T>
	class GameObject : public Entity<T>, public IGameObject
	{
	public:
		GameObject()
		{
			AddComponent<Transform>(Transform());
		}
		virtual void Update() = 0;
	};
}