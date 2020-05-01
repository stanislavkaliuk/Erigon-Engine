#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <unordered_map>
namespace ECS
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void OnEntityDestroyed(Entity entity) = 0;
	};

	template<class T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(Entity entity, T component)
		{
			assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");

			size_t newIndex = size;
			entityToIndexMap[entity] = newIndex;
			indexToEntityMap[newIndex] = entity;
			componentArray[newIndex] = std::make_shared<T>(component);
			size++;
		}

		void RemoveData(Entity entity)
		{
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Tried to removed non-existed component");
			size_t indexOfEntity = entityToIndexMap[entity];
			size_t indexOfLastElement = size - 1;
			componentArray[indexOfEntity] = componentArray[indexOfLastElement];

			Entity lastElementEntity = indexToEntityMap[indexOfLastElement];
			entityToIndexMap[lastElementEntity] = indexOfEntity;
			indexToEntityMap[indexOfEntity] = lastElementEntity;

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(indexOfLastElement);

			size--;
		}

		std::shared_ptr<T> GetData(Entity entity)
		{
			return componentArray[entityToIndexMap[entity]];
		}

		void OnEntityDestroyed(Entity entity) override
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		std::array<std::shared_ptr<T>, MAX_ENTITIES> componentArray{};
		std::unordered_map<Entity, size_t> entityToIndexMap{};
		std::unordered_map<Entity, size_t> indexToEntityMap{};
		size_t size;
	};
}