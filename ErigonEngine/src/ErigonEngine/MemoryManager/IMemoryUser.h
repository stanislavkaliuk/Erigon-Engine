#pragma once

namespace ErigonEngine
{
	class MemoryManager;
	class IMemoryUser
	{
	public:
		IMemoryUser();
		virtual ~IMemoryUser();

		inline const void* allocate(size_t memSize, const char* user = nullptr);
		inline void free(void* pMemory);

	private:
		MemoryManager* memoryManager;
	};
}