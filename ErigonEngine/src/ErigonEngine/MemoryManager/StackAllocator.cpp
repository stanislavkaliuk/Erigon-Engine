#include "eepch.h"
#include "StackAllocator.h"

namespace ErigonEngine
{
	StackAllocator::StackAllocator(size_t memSize, const void* memory) : IAllocator(memSize, memory) {}

	StackAllocator::~StackAllocator()
	{
		this->clear();
	}

	void* StackAllocator::alloc(size_t memSize, uint8_t alignment)
	{
		union
		{
			void* vPtr;
			uintptr_t uiPtr;
			AllocMetaInfo* meta;
		};

		vPtr = (void*)this->begin;
		uiPtr += this->used;
		uint8_t memAdjustment = GetAdjustment(vPtr, alignment, sizeof(AllocMetaInfo));

		if (this->used + memSize + memAdjustment > this->size)
		{
			return nullptr;
		}

		meta->adjustment = memAdjustment;
		uiPtr += memAdjustment;

		this->used += memSize + memAdjustment;
		this->allocations++;

		return vPtr;
	}

	void StackAllocator::free(void* pMemory)
	{
		union
		{
			void* vPtr;
			uintptr_t uiPtr;
			AllocMetaInfo* meta;
		};

		vPtr = pMemory;
		uiPtr -= sizeof(AllocMetaInfo);

		this->used -= ((uintptr_t)this->begin + this->used) - ((uintptr_t)pMemory + meta->adjustment);
		this->allocations--;
	}

	void StackAllocator::clear()
	{
		this->used = 0;
		this->allocations = 0;
	}

}
