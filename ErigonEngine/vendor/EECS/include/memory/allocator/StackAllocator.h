#pragma once
#include "IAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API StackAllocator : public IAllocator
		{
		private:
			struct AllocMetaInfo
			{
				uint8 adjustment;
			};

		public:
			StackAllocator(size_t memSize, const void* memory);
			virtual ~StackAllocator();
			virtual void* Allocate(size_t size, uint8 alignment) override;
			virtual void Free(void* p) override;
			virtual void Clear() override;
		};
	}
}