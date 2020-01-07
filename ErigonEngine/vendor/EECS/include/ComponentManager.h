#pragma once
#include "EECS_API.h"
#include "EECSController.h"
#include "IComponent.h"
#include "tools/TypeID.h"
#include "memory/ChunkAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API ComponentManager : GlobalMemoryUser
		{
			friend class IComponent;

			class IComponentContainer
			{
			public:
				virtual ~IComponentContainer() {}
				virtual const char* GetComponentContainerTypeName() const = 0;
				virtual void DestroyComponent(IComponent* object) = 0;
			};

			template<class T>
			class ComponentContainer : public ChunkAllocator<T, COMPONENT_CHUNCK_SIZE>, public IComponentContainer
			{
				ComponentContainer(const ComponentContainer&) = delete;
				ComponentContainer& operator=(ComponentContainer&) = delete;

			public:
				ComponentContainer() : ChunkAllocator("ComponentManager"){}
				virtual ~ComponentContainer() {}

				virtual const char* GetComponentContainerTypeName() const override
				{
					return typeid(T).name();
				}

				virtual void DestroyComponent(IComponent* object) override
				{
					object->~IComponent();
					this->DestroyObject(object);
				}
			};

			ComponentManager(const ComponentManager&) = delete;
			ComponentManager& operator=(ComponentManager&) = delete;
			using ComponentContainerRegistry = std::unordered_map<ComponentTypeID, IComponentContainer*>;

			ComponentContainerRegistry componentContainerRegistry;

			template<class T>
			inline ComponentContainer<T>* GetComponentContainer()
			{
				ComponentTypeID componentId = T::COMPONENT_TYPE_ID;

				auto it = this->componentContainerRegistry.find(componentId);
				ComponentContainer<T>* cc = nullptr;

				if (it == this->componentContainerRegistry.end())
				{
					cc = new ComponentContainer<T>();
					this->componentContainerRegistry[componentId] = cc;
				}
				else
				{
					cc = static_cast<ComponentContainer<T>*>(it->second);
				}

				return cc;
			}

			using ComponentLookupTable = std::vector<IComponent*>;
			ComponentLookupTable componentTable;

			using EntityComponentMap = std::vector<std::vector<ComponentID>>;
			EntityComponentMap entityComponentMap;

			ComponentID	AqcuireComponentId(IComponent* component);
			void ReleaseComponentId(ComponentID id);
			void MapEntityComponent(EntityID entityId, ComponentID componentId, ComponentTypeID componentTypeId);
			void UnmapEntityComponent(EntityID entityId, ComponentID componentId, ComponentTypeID componentTypeId);

		public:
			template<class T>
			using ComponentIterator = typename ComponentContainer<T>::iterator;

			ComponentManager();
			~ComponentManager();

			template<class T, class ... ARGS>
			T* AddComponent(const EntityID entityId, ARGS&&...args)
			{
				static constexpr std::hash<ComponentID> ComponentIDHasher{ std::hash<ComponentID>() };

				const ComponentTypeID componentTypeId = T::COMPONENT_TYPE_ID;
				void* objectMemoryP = GetComponentContainer<T>->CreateObject();
				ComponentID componentId = this->AqcuireComponentId((T*)objectMemoryP);
				((T*)objectMemoryP)->componentID = componentId;

				IComponent* component = new(objectMemoryP)T(std::forward<ARGS>(args)...);
				component->owner = entityId;
				component->hashValue = ComponentIDHasher(entityId) ^ (ComponentIDHasher(componentId) << 1);
				MapEntityComponent(entityId, componentId, componentTypeId);
				return static_cast<T*>(component);
			}

			template<class T>
			void RemoveComponent(const EntityID entityId)
			{
				const ComponentTypeID componentTypeId = T::COMPONENT_TYPE_ID;
				const ComponentID componentId = this->entityComponentMap[entityId.index][componentTypeId];
				IComponent* component = this->componentTable[componentId];
				GetComponentContainer<T>->DestroyObject(component);
				UnmapEntityComponent(entityId, componentId, componentTypeId);
			}

			void RemoveAllComponents(const EntityID entityId)
			{
				static const size_t COMPONENTS_AMOUNT = this->entityComponentMap[0].size();
				for (ComponentTypeID componentTypeId = 0; componentTypeId < COMPONENTS_AMOUNT; ++componentTypeId)
				{
					const ComponentID componentId = this->entityComponentMap[entityId.index][componentTypeId];
					if (componentId == INVALID_COMPONENT_ID)
					{
						continue;
					}

					IComponent* component = this->componentTable[componentId];
					if (component != nullptr)
					{
						auto it = this->componentContainerRegistry.find(componentTypeId);
						if (it != this->componentContainerRegistry.end())
						{
							it->second->DestroyComponent(component);
						}

						UnmapEntityComponent(entityId, componentId, componentTypeId);
					}
				}
			}
			template<class T>
			std::map<ComponentTypeID, T*> GetAllComponents(const EntityID entityId)
			{
				std::map<ComponentTypeID, T*> resultMap;
				static const size_t COMPONENTS_AMOUNT = this->entityComponentMap[entityId.index].size();
				for (ComponentTypeID componentTypeId = 0; componentTypeId < COMPONENTS_AMOUNT; ++componentTypeId)
				{
					const ComponentID componentId = this->entityComponentMap[entityId.index][componentTypeId];
					if (componentId == INVALID_COMPONENT_ID)
					{
						continue;
					}

					IComponent* component = this->componentTable[componentId];
					if (component != nullptr)
					{
						resultMap.insert(std::make_pair(componentId, static_cast<T*>(component)));
					}
				}

				return resultMap;
			}

			template<class T>
			T* GetComponent(const EntityID entityid)
			{
				const ComponentTypeID componentTypeId = T::COMPONENT_TYPE_ID;
				const ComponentID componentId = this->entityComponentMap[entityid.index][componentTypeId];

				if (componentId == INVALID_COMPONENT_ID)
				{
					return nullptr;
				}

				return static_cast<T*>(this->componentTable[componentId]);
			}

			template<class T>
			inline ComponentIterator<T> begin()
			{
				return GetComponentContainer<T>()->begin();
			}

			template<class T>
			inline ComponentIterator<T> end()
			{
				return GetComponentContainer<T>()->end();
			}

		};
	}
}