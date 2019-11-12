#include "memory/ECSMemory.h"

namespace Erigon
{
	namespace ECS
	{
		MemoryManager::MemoryManager()
		{
			this->globalMemory = malloc(MemoryManager::MEMORY_CAPACITY);

			this->memoryAllocator = new StackAllocator(MemoryManager::MEMORY_CAPACITY, this->globalMemory);

			this->pendingMemory.clear();
			this->freeMemory.clear();
		}

		MemoryManager::~MemoryManager()
		{
			this->memoryAllocator->Clear();
			delete this->memoryAllocator;
			this->memoryAllocator = nullptr;

			free(this->globalMemory);
			this->globalMemory = nullptr;
		}

		void MemoryManager::CheckMemoryLeaks()
		{

		}
	}
}