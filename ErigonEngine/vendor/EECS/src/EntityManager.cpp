#include "EntityManager.h"

namespace Erigon
{
	namespace ECS
	{
		EntityManager::EntityManager(ComponentManager* componentManager) :
			pendingDestroyedEntites(1024),
			numPendingDestroyedEntites(0),
			componentManager(componentManager)
		{}

		EntityManager::~EntityManager()
		{
			for (auto ec : this->entityRegistry)
			{
				delete ec.second;
				ec.second = nullptr;
			}
		}

		EntityID EntityManager::AqcuireEntityId(IEntity* entity)
		{
			return this->entityHandleTable.AqcuireHandle(entity);
		}

		void EntityManager::ReleaseEntityId(EntityID id)
		{
			this->entityHandleTable.ReleaseHandler(id);
		}

		void EntityManager::RemoveDestroyedEntities()
		{
			for (size_t index = 0; index < this->numPendingDestroyedEntites; index++)
			{
				EntityID entityid = this->pendingDestroyedEntites[index];
				IEntity* entity = this->entityHandleTable[entityid];

				const EntityTypeID entityTypeId = entity->GetEntityTypeID();

				auto it = this->entityRegistry.find(entityTypeId);
				if (it != this->entityRegistry.end())
				{
					this->componentManager->RemoveAllComponents(entityid);
					it->second->DestroyEntity(entity);
				}

				this->ReleaseEntityId(entityid);
			}
			this->numPendingDestroyedEntites = 0;
		}
	}
}