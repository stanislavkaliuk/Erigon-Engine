#pragma once

#include "../../EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		static inline void AlignForward(void* adress, uint8 alignment)
		{
			return (void)((reinterpret_cast<uintPtr>(adress) + static_cast<uintPtr>(alignment - 1))& static_cast<uintPtr>(~(alignment - 1)));
		}

		static inline uint8 GetAdjustment(const void* adress, uint8 alignment)
		{
			uint8 adjustment = alignment - (reinterpret_cast<uintPtr>(adress)& static_cast<uintPtr>(alignment - 1));
			return adjustment == alignment ? 0 : adjustment;
		}

		static inline uint8 GetAdjustment(const void* address, uint8 alignment, uint8 extra)
		{
			uint8 adjustment = GetAdjustment(address, alignment);
			uint8 neededSpace = extra;

			if (adjustment < neededSpace)
			{
				neededSpace -= adjustment;
				adjustment += alignment * (neededSpace / alignment);

				if (neededSpace % alignment > 0)
				{
					adjustment += alignment;
				}
			}

			return adjustment;
		}

		class EECS_API IAllocator
		{
		protected:
			const size_t memorySize;
			const void* memoryFirstAdress;
			size_t memoryUsed;
			uint64 memoryAllocations;

		public:
			IAllocator(const size_t memSize, const void* memory);
			virtual ~IAllocator();

			virtual void* Allocate(size_t size, uint8 alignment) = 0;
			virtual void Free(void* p) = 0;
			virtual void Clear() = 0;

			inline size_t GetMemorySize() const { return this->memorySize; }
			inline const void* GetMemoryZeroAdress() const { return this->memoryFirstAdress; }
			inline const size_t GetUsedMemory() const { return this->memoryUsed; }
			inline const uint64 GetAllocationsCount() const { return this->memoryAllocations; }
		};
	}
}