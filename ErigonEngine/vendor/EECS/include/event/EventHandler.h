#pragma once
#include "EECS_API.h"
#include "memory/allocator/LinearAllocator.h"
#include "IEvent.h"
#include "EventDispatcher.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API EventHandler : GlobalMemoryUser
		{
			friend class EECSController;

			using EventDispatcherMap = std::unordered_map<EventTypeID, IEventDispatcher*>;
			using EventStorage = std::vector<IEvent*>;
			using EventMemoryAllocator = LinearAllocator;

		private:
			EventHandler(const EventHandler&);
			EventHandler& operator==(EventHandler&);

			EventDispatcherMap eventDispatcherMap;
			EventMemoryAllocator* memoryAllocator;

			EventStorage eventStorage;

			template<class E>
			inline void AddEventCallback(IEventDelegate* const eventDelegate)
			{
				EventTypeID eventTypeID = T::EVENT_TYPE_ID;
				EventDispatcherMap::const_iterator it = this->eventDispatcherMap.find(eventTypeID);
				if (it == this->eventDispatcherMap.end())
				{
					std::pair<EventTypeID, IEventDispatcher*> kvp(eventTypeID, EventDispatcher<E>());
					kvp.second->AddEventCallback(eventDelegate);
					this->eventDispatcherMap.insert(kvp);
				}
				else
				{
					this->eventDispatcherMap[eventTypeID]->AddEventCallback(eventDelegate);
				}
			}

			inline void RemoveEventCallback(IEventDelegate* eventDelegate)
			{
				auto eventTypeId = eventDelegate->GetEventTypeID();
				EventDispatcherMap::const_iterator it = this->eventDispatcherMap.find(eventTypeId);
				if (it != this->eventDispatcherMap.end())
				{
					this->eventDispatcherMap[eventTypeId]->RemoveEventCallback(eventDelegate);
				}
			}

		public:
			EventHandler();
			~EventHandler();

			inline void ClearEventBuffer()
			{
				this->memoryAllocator->Clear();
				this->eventStorage.clear();
			}

			inline void ClearDispatcherEvent()
			{
				this->eventDispatcherMap.clear();
			}

			template<class E, class...ARGS>
			void Send(ARGS&&...args)
			{
				void* memP = this->memoryAllocator->Allocate(sizeof(E), alignof(E));
				if (memP != nullptr)
				{
					this->eventStorage.push_back(new (memP)E(std::forward<ARGS>(args)...));
				}
			}

			void DispatchEvents()
			{
				size_t lastIndex = this->eventStorage.size();
				size_t thisIndex = 0;
				while (thisIndex < lastIndex)
				{
					auto event = this->eventStorage[thisIndex++];
					if (event == nullptr)
					{
						continue;
					}

					auto it = this->eventDispatcherMap.find(event->GetEventTypeID());
					if (it == this->eventDispatcherMap.end())
					{
						continue;
					}

					it->second->Dispatch(event);
					lastIndex = this->eventStorage.size();
				}

				ClearEventBuffer();
			}
		};
	}
}