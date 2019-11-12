#pragma once
#define ECS_GLOBAL_MEMORY_CAPACITY 134217728 //128mb

#include "EECS_API.h"
#include "allocator/StackAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		class StackAllocator;

		class MemoryManager
		{
			friend class GlobalMemoryUser;

		public:
			static constexpr size_t MEMORY_CAPACITY = ECS_GLOBAL_MEMORY_CAPACITY;

		private:
			void* globalMemory;
			StackAllocator* memoryAllocator;
			std::vector<std::pair<const char*, void*>> pendingMemory;
			std::list<void*> freeMemory;

			MemoryManager(const MemoryManager&) = delete;
			MemoryManager& operator=(MemoryManager&) = delete;

		public:
			MemoryManager();
			~MemoryManager();

			inline void* Allocate(size_t memSize, const char* user = nullptr)
			{
				void* memoryP = memoryAllocator->Allocate(memSize, alignof(uint8));
				this->pendingMemory.push_back(std::pair<const char*, void*>(user, memoryP));
				return memoryP;
			}

			inline void Free(void* memP)
			{
				if (memP == this->pendingMemory.back().second)
				{
					this->memoryAllocator->Free(memP);
					this->pendingMemory.pop_back();

					bool checked = true;
					while (checked)
					{
						checked = false;
						for (auto it : this->freeMemory)
						{
							if (it == this->pendingMemory.back().second)
							{
								this->memoryAllocator->Free(memP);
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
					this->freeMemory.push_back(memP);
				}
			}

			void CheckMemoryLeaks();
		};
	}
}