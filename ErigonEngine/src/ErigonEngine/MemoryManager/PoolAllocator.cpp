#include "eepch.h"
#include "PoolAllocator.h"

namespace ErigonEngine
{
	PoolAllocator::PoolAllocator(size_t memSize, const void* pMemory, size_t objectSize, uint8_t objectAlignment) : IAllocator(memSize, pMemory), object_size(objectSize), object_alignment(objectAlignment)
	{
		this->clear();
	}

	PoolAllocator::~PoolAllocator()
	{
		this->freeList = nullptr;
	}

	void* PoolAllocator::alloc(size_t memSize, uint8_t alignment)
	{
		if (this->freeList == nullptr)
		{
			return nullptr;
		}

		void* pFreeList = this->freeList;
		this->used += this->object_size;
		this->allocations++;

		return pFreeList;
	}


	void PoolAllocator::free(void* pMemory)
	{
		*((void**)pMemory) = this->freeList;
		this->freeList = (void**)pMemory;

		this->used -= this->object_size;
		this->allocations--;
	}

	void PoolAllocator::clear()
	{
		uint8_t adjustment = GetAdjustment(this->begin, this->object_alignment);
		size_t objNum = (size_t)floor((this->size - adjustment) / this->object_size);

		union
		{
			void* vPtr;
			uintptr_t uiPtr;
		};

		vPtr = (void*)this->begin;
		uiPtr += adjustment;

		this->freeList = (void**)vPtr;

		void** pFreeList = this->freeList;

		for (int index = 0; index < objNum - 1; index++)
		{
			*pFreeList = (void*)((uintptr_t)pFreeList + this->object_size);
			pFreeList = (void**)*pFreeList;
		}

		*pFreeList = nullptr;
	}


}
