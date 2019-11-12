#pragma once

#include "IEntity.h"

namespace Erigon
{
	namespace ECS
	{
		using ComponentID = objectID;
		using ComponentTypeID = typeID;

		static const ComponentID INVALID_COMPONENT_ID = INVALID_OBJ_ID;

		template<class T>
		class Component;

		class EECS_API IComponent
		{
			friend class ComponentManager;

		protected:
			ComponentID hashValue;
			ComponentID componentID;
			EntityID owner;
			bool enabled;

		public:
			IComponent();
			virtual ~IComponent();

			inline const bool operator==(const IComponent& other) const { return hashValue == other.hashValue; }
			inline const bool operator!=(const IComponent& other) const { return hashValue != other.hashValue; }

			inline const ComponentID GetComponentID() const { return this->componentID; }
			inline const EntityID GetOwner() const { return this->owner; }

			inline void SetActive(bool state) { this->enabled = state; }
			inline bool IsActive() const { return this->enabled; }
		};
	}
}