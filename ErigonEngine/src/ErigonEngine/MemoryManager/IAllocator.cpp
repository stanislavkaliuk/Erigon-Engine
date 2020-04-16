#include "eepch.h"
#include "IAllocator.h"

namespace ErigonEngine
{
	IAllocator::IAllocator(const size_t memorySize, const void* pMemory) : size(memorySize), begin(pMemory), used(0), allocations(0)
	{
	}

	IAllocator::~IAllocator() {}
}
