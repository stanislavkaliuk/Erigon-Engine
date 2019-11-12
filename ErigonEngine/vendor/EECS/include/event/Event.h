#pragma once
#include "IEvent.h"
#include "tools/TypeID.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class Event : public IEvent
		{
		public:
			static const EventTypeID EVENT_TYPE_ID;
			Event() : IEvent(EVENT_TYPE_ID) {}
		};

		template<class T>
		const EventTypeID Event<T>::EVENT_TYPE_ID{ typeid(T).hash_code() };
	}
}