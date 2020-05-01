#pragma once

#include "ComponentArray.hpp"
#include "Types.hpp"

#include <any>
#include <memory>
#include <unordered_map>

namespace ECS
{
	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component more than once.");

			componentTypes.insert({ typeName, nextComponentType });
			componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			nextComponentType++;
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return componentTypes[typeid(T).name()];
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		std::shared_ptr<T> GetComponent(Entity entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : componentArrays)
			{
				auto const& component = pair.second;
				component->OnEntityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> componentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
		ComponentType nextComponentType{};

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeid(T).name()]);
		}
	};
}