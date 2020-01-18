#pragma once
#include "EECS_API.h"
#include "IComponent.h"
#include "tools/TypeID.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class Component : public IComponent
		{
		public:
			static const ComponentTypeID COMPONENT_TYPE_ID;

			Component() {}
			virtual ~Component() {}

			inline ComponentTypeID GetComponentTypeID() const { return COMPONENT_TYPE_ID; }
		};

		template<class T>
		const ComponentTypeID Component<T>::COMPONENT_TYPE_ID = TypeID<IComponent>::Get<T>();
	}
}