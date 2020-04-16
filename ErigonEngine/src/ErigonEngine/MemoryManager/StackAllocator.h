#pragma once
#include "IAllocator.h"

namespace ErigonEngine
{
	class StackAllocator : public IAllocator
	{
	public:
		StackAllocator(size_t memSize, const void* memory);
		virtual ~StackAllocator();
		virtual void* alloc(size_t size, uint8_t alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;

	private:
		struct AllocMetaInfo
		{
			uint8_t adjustment;
		};
	};
}