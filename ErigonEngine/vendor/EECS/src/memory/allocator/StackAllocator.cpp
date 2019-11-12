#include "memory/allocator/StackAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		StackAllocator::StackAllocator(size_t memSize, const void* memP) : IAllocator(memSize, memP)
		{}

		StackAllocator::~StackAllocator()
		{
			this->Clear();
		}

		void* StackAllocator::Allocate(size_t memSize, uint8 alignment)
		{
			union
			{
				void* ptr;
				uintPtr uptr;
				AllocMetaInfo* meta;
			};

			ptr = (void*)this->memoryFirstAdress;
			uptr += this->memoryUsed;
			uint8 memAdjustment = GetAdjustment(ptr, alignment, sizeof(AllocMetaInfo));

			if (this->memoryUsed + memSize + memAdjustment > this->memorySize)
			{
				return nullptr;
			}

			meta->adjustment = memAdjustment;
			uptr += memAdjustment;

			this->memoryUsed += memSize + memAdjustment;
			this->memoryAllocations++;

			return ptr;
		}

		void StackAllocator::Free(void* mem)
		{
			union
			{
				void* ptr;
				uintPtr uptr;
				AllocMetaInfo* meta;
			};

			ptr = mem;
			uptr -= sizeof(AllocMetaInfo);

			this->memoryUsed -= ((uintPtr)this->memoryFirstAdress + this->memoryUsed) - ((uintPtr)mem + meta->adjustment);
			this->memoryAllocations--;
		}

		void StackAllocator::Clear()
		{
			this->memoryUsed = 0;
			this->memoryAllocations = 0;
		}
	}
}