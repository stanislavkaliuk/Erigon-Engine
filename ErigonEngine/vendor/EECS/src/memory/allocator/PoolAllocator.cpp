#include "memory/allocator/PoolAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		PoolAllocator::PoolAllocator(size_t memSize, const void* memP, size_t objSize, uint8 objectAlignment) : IAllocator(memSize, memP),
																												OBJECT_SIZE(objSize),
																												OBJECT_ALIGNMENT(objectAlignment)
		{
			this->Clear();
		}

		PoolAllocator::~PoolAllocator()
		{
			this->freeList = nullptr;
		}

		void* PoolAllocator::Allocate(size_t memSize, uint8 alignment)
		{
			if (this->freeList == nullptr)
			{
				return nullptr;
			}

			void* p = this->freeList;
			this->memoryUsed += this->OBJECT_SIZE;
			this->memoryAllocations++;

			return p;
		}

		void PoolAllocator::Free(void* memory)
		{
			*((void**)memory) = this->freeList;
			this->freeList = (void**)memory;

			this->memoryUsed -= this->OBJECT_SIZE;
			this->memoryAllocations--;
		}

		void PoolAllocator::Clear()
		{
			uint8 adjustment = GetAdjustment(this->memoryFirstAdress, this->OBJECT_ALIGNMENT);
			size_t numObjs = (size_t)floor((this->memorySize - adjustment) / this->OBJECT_SIZE);

			union
			{
				void* ptr;
				uintPtr uptr;
			};

			ptr = (void*)this->memoryFirstAdress;
			uptr += adjustment;

			this->freeList = (void**)ptr;

			void** p = this->freeList;

			for (int i = 0; i < numObjs - 1; i++)
			{
				*p = (void*)((uintPtr)p + this->OBJECT_SIZE);
				p = (void**)*p;
			}

			*p = nullptr;
		}
	}
}