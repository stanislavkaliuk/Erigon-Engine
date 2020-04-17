#pragma once
#include "IAllocator.h"

namespace ErigonEngine
{

	/*
			  1			2	   3     4	    N
		||==========|=======|=====|=====| .... ||
		^										^
	Memory Begin				Last available memory address
	  (begin)							(begin + memSize)
	*/

	class LinearAllocator : public IAllocator
	{
	public:
		LinearAllocator(size_t memSize, const void* pMemory);
		virtual ~LinearAllocator();
		virtual void* alloc(size_t size, uint8_t alignment) override;
		virtual void free(void* pMemory) override;
		virtual void clear() override;
	};
}