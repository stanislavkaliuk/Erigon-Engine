#pragma once

#include "EECS_API.h"
#include "EECSController.h"
#include "IEntity.h"
#include "ComponentManager.h"
#include "memory/ChunkAllocator.h"
#include "tools/Handle.h"

namespace Erigon
{
	namespace ECS
	{
		using EntityHandleTable = HandleTable<IEntity, EntityID>;

		class EECS_API EntityManager
		{
			class IEntityContainer
			{
			public:
				virtual ~IEntityContainer() {}
				virtual const char* GetEntityContainerTypeName() const = 0;
				virtual void DestroyEntity(IEntity* object) = 0;
			};

			template<class T>
			class EntityContainer : public ChunkAllocator<T, ENTITY_CHUNK_SIZE>, public IEntityContainer
			{
				EntityContainer(const EntityContainer&) = delete;
				EntityContainer& operator=(EntityContainer&) = delete;

			public:
				EntityContainer() :ChunkAllocator("EntityManager") {}
				virtual ~EntityContainer() {}

				virtual const char* GetEntityContainerTypeName() const override { return typeid(T).name(); }
				virtual void DestroyEntity(IEntity* object) override
				{
					object->~IEntity();
					this->DestroyObject(object);
				}
			};

			using EntityRegistry = std::unordered_map<EntityTypeID, IEntityContainer*>;
			EntityRegistry entityRegistry;

			using PendingDestroyedEntities = std::vector<EntityID>;
			PendingDestroyedEntities pendingDestroyedEntites;
			size_t numPendingDestroyedEntites;

			ComponentManager* componentManager;

		private:
			EntityManager(const EntityManager&) = delete;
			EntityManager& operator=(EntityManager&) = delete;

			EntityHandleTable entityHandleTable;

			template<class T>
			inline EntityContainer<T>* GetEntityContainer()
			{
				EntityTypeID id = T::ENTITY_TYPE_ID;
				auto it = this->entityRegistry.find(id);
				EntityContainer<T>* ec = nullptr;
				if (it == this->entityRegistry.end())
				{
					ec = new EntityContainer<T>();
					this->entityRegistry[id] = ec;
				}
				else
				{
					ec = (EntityContainer<T>*)it->second;
				}

				return ec;
			}

			EntityID AqcuireEntityId(IEntity* entity);
			void ReleaseEntityId(EntityID entityid);

		public:
			EntityManager(ComponentManager* componentManager);
			~EntityManager();

			template<class T, class... ARGS>
			EntityID CreateEntity(ARGS&&... args)
			{
				void* objectMemoryP = GetEntityContainer<T>()->CreateObject();
				EntityID entityId = this->AqcuireEntityId((T*)objectMemoryP);

				((T*)objectMemoryP)->entityId = entityId;
				((T)objectMemoryP)->componentManager = this->componentManager;

				IEntity* entity = new (objectMemoryP)T(std::forward<ARGS>(args)...);
				return entityId;
			}

			void DestroyEntity(EntityID entityId)
			{
				IEntity* entity = this->entityHandleTable[entityId];
				const EntityTypeID id = entity->GetEntityTypeID();
				if (this->numPendingDestroyedEntites < this->pendingDestroyedEntites.size())
				{
					this->pendingDestroyedEntites[this->numPendingDestroyedEntites++] = entityId;
				}
				else
				{
					this->pendingDestroyedEntites.push_back(entityId);
					this->numPendingDestroyedEntites++;
				}
			}

			inline IEntity* GetEntity(EntityID entityId)
			{
				return this->entityHandleTable[entityId];
			}

			inline EntityID GetEntityID(EntityID::value_type index) const { return this->entityHandleTable[index]; }

			void RemoveDestroyedEntities();
		};
	}
}