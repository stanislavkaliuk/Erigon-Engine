#pragma once
#include "IAllocator.h"

namespace ErigonEngine
{
	class PoolAllocator : public IAllocator
	{
	public:
		PoolAllocator(size_t memSize, const void* pMemory, size_t objectSize, uint8_t objectAlignment);
		virtual ~PoolAllocator();

		virtual void* alloc(size_t memSize, uint8_t alignment) override;
		virtual void free(void* pMemory) override;
		virtual void clear() override;

	private:
		const size_t object_size;
		const uint8_t object_alignment;
		void** freeList;
	};
}