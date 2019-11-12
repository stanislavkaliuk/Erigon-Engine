#include "event/EventHandler.h"

namespace Erigon
{
	namespace ECS
	{
		EventHandler::EventHandler()
		{
			this->memoryAllocator = new EventMemoryAllocator(EECS_EVENT_MEMORY_BUFFER_SIZE, Allocate(EECS_EVENT_MEMORY_BUFFER_SIZE, "EventHandler"));
			this->eventStorage.reserve(1024);
		}

		EventHandler::~EventHandler()
		{
			for (EventHandler::EventDispatcherMap::iterator it = this->eventDispatcherMap.begin(); it != this->eventDispatcherMap.end(); it++)
			{
				delete (*it).second;
				(*it).second = nullptr;
			}

			this->eventDispatcherMap.clear();
			Free((void*)this->memoryAllocator->GetMemoryZeroAdress());
			delete this->memoryAllocator;
			this->memoryAllocator = nullptr;
		}
	}
}