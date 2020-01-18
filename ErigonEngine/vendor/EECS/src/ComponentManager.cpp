#include "ComponentManager.h"

namespace Erigon
{
	namespace ECS
	{
		ComponentManager::ComponentManager()
		{
			const size_t NUM_COMPONENTS{ TypeID<IComponent>::Get() };

			this->entityComponentMap.resize(ENTITY_TABLE_GROW);
			for (auto i = 0; i < ENTITY_TABLE_GROW; i++)
			{
				this->entityComponentMap[i].resize(NUM_COMPONENTS, INVALID_COMPONENT_ID);
			}
		}

		ComponentManager::~ComponentManager()
		{
			for (auto cc : this->componentContainerRegistry)
			{
				delete cc.second;
				cc.second = nullptr;
			}
		}

		ComponentID ComponentManager::AqcuireComponentId(IComponent* component)
		{
			int i = 0;
			for (; i < this->componentTable.size(); i++)
			{
				if (this->componentTable[i] == nullptr)
				{
					this->componentTable[i] = component;
					return i;
				}
			}

			this->componentTable.resize(this->componentTable.size() + COMPONENT_TABLE_GROW, nullptr);
			this->componentTable[i] = component;

			return i;
		}

		void ComponentManager::ReleaseComponentId(ComponentID id)
		{
			this->componentTable[id] = nullptr;
		}

		void ComponentManager::MapEntityComponent(EntityID entityId, ComponentID componentId, ComponentTypeID componentTypeId)
		{
			static const size_t NUM_COMPONENTS{ TypeID<IComponent>::Get() };
			if ((this->entityComponentMap.size() - 1) < entityId.index)
			{
				size_t oldSize = this->entityComponentMap.size();
				size_t newSize = oldSize + ENTITY_TABLE_GROW;
				this->entityComponentMap.resize(newSize);

				for (auto i = oldSize; i < newSize; i++)
				{
					this->entityComponentMap[i].resize(NUM_COMPONENTS, INVALID_COMPONENT_ID);
				}
			}

			this->entityComponentMap[entityId.index][componentTypeId] = componentId;
		}

		void ComponentManager::UnmapEntityComponent(EntityID entityId, ComponentID componentId, ComponentTypeID componentTypeId)
		{
			this->entityComponentMap[entityId.index][componentTypeId] = INVALID_COMPONENT_ID;
			this->ReleaseComponentId(componentId);
		}
	}
}