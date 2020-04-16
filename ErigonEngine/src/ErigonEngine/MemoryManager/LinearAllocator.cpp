#include "eepch.h"
#include "LinearAllocator.h"

namespace ErigonEngine
{
	LinearAllocator::LinearAllocator(size_t memSize, const void* pMemory) : IAllocator(memSize, pMemory) {}

	LinearAllocator::~LinearAllocator()
	{
		this->clear();
	}

	void* LinearAllocator::alloc(size_t memSize, uint8_t alignment)
	{
		union
		{
			void* vPtr;
			uintptr_t uiPtr;
		};

		vPtr = (void*)this->begin;
		uiPtr += this->used;

		uint8_t adjustment = GetAdjustment(vPtr, alignment);

		if (this->used + memSize + adjustment > this->size)
		{
			//TODO: Throw an exception
			return nullptr;
		}

		uiPtr += adjustment;
		this->used += memSize + adjustment;
		this->allocations++;

		return vPtr;
	}

	void LinearAllocator::free(void* pMemory)
	{
		assert(false && "Linear allocators do not support free operations. Use clear instead.");
	}

	void LinearAllocator::clear()
	{
		this->used = 0;
		this->allocations = 0;
	}
}
