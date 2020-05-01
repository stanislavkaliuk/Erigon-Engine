#pragma once
#include "Types.hpp"

#include <array>
#include <cassert>
#include <queue>

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager() : livingEntitiesAmount(0)
		{
			for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
			{
				availableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			Entity id = availableEntities.front();
			availableEntities.pop();
			livingEntitiesAmount++;

			return id;
		}

		void DestroyEntity(Entity entity)
		{
			signatures[entity].reset();
			availableEntities.push(entity);
			livingEntitiesAmount--;
		}

		void SetSignature(Entity entity, Signature signature)
		{
			signatures[entity] = signature;
		}

		Signature GetSignature(Entity entity)
		{
			return signatures[entity];
		}

	private:
		std::queue<Entity> availableEntities{};
		std::array<Signature, MAX_ENTITIES> signatures{};
		uint32_t livingEntitiesAmount;
	};
}