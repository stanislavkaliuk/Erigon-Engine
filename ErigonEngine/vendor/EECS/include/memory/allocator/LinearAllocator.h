#pragma once
#include "IAllocator.h"
namespace Erigon
{
	namespace ECS
	{
		class EECS_API LinearAllocator : public IAllocator
		{
		public:
			LinearAllocator(size_t memSize, const void* memory);
			virtual ~LinearAllocator();
			virtual void* Allocate(size_t size, uint8 alignment) override;
			virtual void Free(void* p) override;
			virtual void Clear() override;
		};
	}
}