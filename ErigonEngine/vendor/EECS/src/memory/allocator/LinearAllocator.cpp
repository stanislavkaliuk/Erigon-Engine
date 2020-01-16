#include "memory/allocator/LinearAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		LinearAllocator::LinearAllocator(size_t memSize, const void* memP) : IAllocator(memSize, memP) {}
		LinearAllocator::~LinearAllocator()
		{
			this->Clear();
		}

		void* LinearAllocator::Allocate(size_t memSize, uint8 alignment)
		{
			union
			{
				void* voidPtr;
				uintPtr uIntPtr;
			};

			voidPtr = (void*)this->memoryFirstAdress;
			uIntPtr += this->memoryUsed;

			uint8 adjustment = GetAdjustment(voidPtr, alignment);

			if (this->memoryUsed + memSize + adjustment > this->memorySize)
			{
				return nullptr;
			}

			uIntPtr += adjustment;
			this->memoryUsed += memSize + adjustment;
			this->memoryAllocations++;

			return voidPtr;
		}

		void LinearAllocator::Free(void* mem)
		{

		}

		void LinearAllocator::Clear()
		{
			this->memoryUsed = 0;
			this->memoryAllocations = 0;
		}
	}
}