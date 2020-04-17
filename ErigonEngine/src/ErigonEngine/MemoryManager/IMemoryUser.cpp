#include "eepch.h"
#include "MemoryManager.h"

namespace ErigonEngine
{
	MemoryManager* engineMemoryManager = new MemoryManager();

	IMemoryUser::IMemoryUser() : memoryManager(engineMemoryManager) {}

	IMemoryUser::~IMemoryUser() {}

	inline const void* IMemoryUser::allocate(size_t memSize, const char* user)
	{
		return memoryManager->Allocate(memSize, user);
	}

	inline void IMemoryUser::free(void* pMemory)
	{
		memoryManager->Free(pMemory);
	}
}
