#pragma once
#include "IAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API PoolAllocator : public IAllocator
		{
		private:
			const size_t OBJECT_SIZE;
			const uint8 OBJECT_ALIGNMENT;
			void** freeList;

		public:

			PoolAllocator(size_t memSize, const void* memory, size_t objectSize, uint8 objectAlignment);
			virtual ~PoolAllocator();

			virtual void* Allocate(size_t size, uint8 alignment) override;
			virtual void Free(void* p) override;
			virtual void Clear() override;
		};
	}
}