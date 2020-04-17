#pragma once
#include <cstdint>

namespace ErigonEngine
{

	static inline void AlignForward(void* address, uint8_t alignment)
	{
		return (void)((reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) & static_cast<uintptr_t>(~(alignment - 1)));
	}

	static inline uint8_t GetAdjustment(const void* address, uint8_t alignment)
	{
		uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1));
		return adjustment == alignment ? 0 : adjustment;
	}

	static inline uint8_t GetAdjustment(const void* address, uint8_t alignment, uint8_t extra)
	{
		uint8_t adjustment = GetAdjustment(address, alignment);
		uint8_t space = extra;

		if (adjustment < space)
		{
			space -= adjustment;
			adjustment += alignment * (space / alignment);

			if (space % alignment > 0)
			{
				adjustment += alignment;
			}
		}

		return adjustment;
	}

	class IAllocator
	{
	protected:
		const size_t size;
		const void* begin;
		size_t used;
		uint64_t allocations;

	public:
		IAllocator(const size_t memorySize, const void* memory);
		virtual ~IAllocator();

		virtual void* alloc(size_t size, uint8_t alignment) = 0;
		virtual void free(void* p) = 0;
		virtual void clear() = 0;

		inline size_t GetMemorySize() const { return this->size; }
		inline const void* GetFirstAddress() const { return this->begin; }
		inline const size_t GetUsedMemory() const { return this->used; }
		inline const uint64_t GetAllocationsCount() const { return this->allocations; }
	};
}