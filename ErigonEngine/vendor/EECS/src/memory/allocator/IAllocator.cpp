#include "memory/allocator/IAllocator.h"

namespace Erigon
{
	namespace ECS
	{
		IAllocator::IAllocator(const size_t memSize, const void* memP) :
								memorySize(memSize), memoryFirstAdress(memP),
								memoryUsed(0), memoryAllocations(0)
		{
		}

		IAllocator::~IAllocator() {}
	}
}