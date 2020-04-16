#include "eepch.h"
#include "MemoryManager.h"
#include "ErigonEngine\Log\Log.h"

namespace ErigonEngine
{
	MemoryManager::MemoryManager()
	{
		this->gMemory = malloc(MemoryManager::MEMORY_CAPACITY);
		this->memoryAllocator = new StackAllocator(MemoryManager::MEMORY_CAPACITY, this->gMemory);
		this->pendingMemory.clear();
		this->freeMemory.clear();
	}

	MemoryManager::~MemoryManager()
	{
		this->memoryAllocator->clear();
		delete this->memoryAllocator;
		this->memoryAllocator = nullptr;

		free(this->gMemory);
		this->gMemory = nullptr;
	}

	void MemoryManager::CheckMemoryLeaks()
	{
		if (this->pendingMemory.size() > 0)
		{
			EE_CORE_FATAL("!!! Memory Leak Detected !!!");

			for (auto i : this->pendingMemory)
			{
				bool isFree = false;

				for (auto j : this->freeMemory)
				{
					if (i.second == j)
					{
						isFree = true;
						break;
					}
				}

				if (!isFree)
				{
					EE_CORE_FATAL("{0} memory user didn't release allocated memory {1}", i.first, i.second);
				}
			}
		}
		else
		{
			EE_CORE_INFO("No memory leaks detected");
		}
	}

}
