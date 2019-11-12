#pragma once

#include "IEntity.h"

namespace Erigon
{
	namespace ECS
	{
		template<class E>
		class Entity : public IEntity
		{
			void operator delete(void*) = delete;
			void operator delete[](void*) = delete;

		public:
			static const EntityTypeID ENTITY_TYPE_ID;

		public:

			virtual const EntityTypeID GetEntityTypeID() const override { return ENTITY_TYPE_ID; }
			Entity() {}
			virtual ~Entity() {}
		};

		template<class E>
		const EntityTypeID Entity<E>::ENTITY_TYPE_ID = TypeID<IEntity>::Get<E>();
	}
}