#pragma once

#define GLOBAL_MEMORY_CAPACITY 536870912 //512mb

#include <vector>
#include <list>

#include "LinearAllocator.h"
#include "IMemoryUser.h"

namespace ErigonEngine
{
	class MemoryManager
	{
		friend class IMemoryUser;

	public:
		MemoryManager();
		~MemoryManager();

		inline void* Allocate(size_t memSize, const char* user = nullptr)
		{
			void* pMemory = memoryAllocator->alloc(memSize, alignof(uint8_t));
			this->pendingMemory.push_back(std::pair<const char*, void*>(user, pMemory));
			return pMemory;
		}

		inline void Free(void* pMemory)
		{
			if (pMemory == this->pendingMemory.back().second)
			{
				this->memoryAllocator->free(pMemory);
				this->pendingMemory.pop_back();


				bool checked = true;

				while (checked)
				{
					checked = false;
					for (auto it : this->freeMemory)
					{
						if (it == this->pendingMemory.back().second)
						{
							this->memoryAllocator->free(pMemory);
							this->pendingMemory.pop_back();
							this->freeMemory.remove(it);

							checked = true;
							break;
						}
					}
				}
			}
			else
			{
				this->freeMemory.push_back(pMemory);
			}
		}

		void CheckMemoryLeaks();

	public:
		static constexpr size_t MEMORY_CAPACITY = GLOBAL_MEMORY_CAPACITY;

	private:
		void* gMemory;
		LinearAllocator* memoryAllocator;
		std::vector<std::pair<const char*, void*>> pendingMemory;
		std::list<void*> freeMemory;

		MemoryManager(const MemoryManager&) = delete;
		MemoryManager& operator=(MemoryManager&) = delete;
	};
}