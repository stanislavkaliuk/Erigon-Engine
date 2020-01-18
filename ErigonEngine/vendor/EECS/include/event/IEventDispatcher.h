#pragma once
#include <unordered_map>
#include "EventDelegate.h"

namespace Erigon
{
	namespace ECS
	{
		class IEvent;
		class IEventDispatcher
		{
		public:
			virtual ~IEventDispatcher() {}
			virtual void Dispatch(IEvent* event) = 0;
			virtual void AddEventCallback(IEventDelegate* const eventDelegate) = 0;
			virtual void RemoveEventCallback(IEventDelegate* eventDelegate) = 0;
			virtual inline size_t GetEventCallbackCount() const = 0;
		};
	}
}