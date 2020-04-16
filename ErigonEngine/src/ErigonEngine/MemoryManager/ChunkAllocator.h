#pragma once

#include "IMemoryUser.h"
#include "PoolAllocator.h"

namespace ErigonEngine
{
	template<class T, size_t maxObjects>
	class ChunkAllocator : protected IMemoryUser
	{
		static const size_t MAX_OBJECTS = maxObjects;
		static const size_t ALLOCATION_SIZE = (sizeof(T) + alignof(T)) * MAX_OBJECTS;
		const char* allocTag;

	public:
		using ObjectList = std::list<T*>;

	public:
		class Chunk
		{
		public:
			Chunk(PoolAllocator* allocator) : allocator(allocator)
			{
				this->chunkStart = reinterpret_cast<uintptr_t>(allocator->GetFirstAddress());
				this->chunkEnd = this->chunkStart + ALLOCATION_SIZE;
				this->objects.clear();
			}

		public:
			PoolAllocator* allocator;
			ObjectList objects;
			uintptr_t chunkStart;
			uintptr_t chunkEnd;
		};

		using Chunks = std::list<Chunk*>;

		class iterator : public std::iterator<std::forward_iterator_tag, T>
		{
			typename Chunks::iterator currentChunk;
			typename Chunks::iterator end;

			typename ObjectList::iterator currentObject;

		public:
			iterator(typename Chunks::iterator begin, typename Chunks::iterator end) : currentChunk(begin), end(end)
			{
				if (begin != end)
				{
					currentObject = (*currentChunk)->objects.begin();
				}
				else
				{
					currentObject = (*std::prev(end))->objects.end();
				}
			}

			inline iterator& operator++()
			{
				currentObject++;
				if (currentObject == (*currentChunk)->objects.end())
				{
					currentChunk++;
					if (currentChunk != end)
					{
						currentObject = (*currentChunk)->objects.begin();
					}
				}
				return *this;
			}

			inline T& operator*() const { return *currentObject; }
			inline T* operator->() const { return *currentObject; }

			inline bool operator==(iterator& other)
			{
				return ((this->currentChunk == other.currentChunk) && (this->currentObject == other.currentObject));
			}

			inline bool operator!=(iterator& other)
			{
				return ((this->currentChunk != other.currentChunk) && (this->currentObject != other.currentObject));
			}
		};

	protected:
		Chunks chunks;

	public:
		ChunkAllocator(const char* allocatorTag = nullptr) : allocTag(allocatorTag)
		{
			PoolAllocator* allocator = new PoolAllocator(ALLOCATION_SIZE, allocate(ALLOCATION_SIZE, allocTag), sizeof(T), alignof(T));
			this->chunks.push_back(new Chunk(allocator));
		}

		virtual ~ChunkAllocator()
		{
			for (auto chunk : this->chunks)
			{
				for (auto obj : chunk->objects)
				{
					((T*)obj)->~T();
				}

				chunk->objects.clear();

				free((void*)chunk->allocator->GetFirstAddress());
				delete chunk->allocator;
				chunk->allocator = nullptr;

				delete chunk;
				chunk = nullptr;
			}
		}

		void* CreateObject()
		{
			void* slot = nullptr;

			for (auto chunk : this->chunks)
			{
				if (chunk->objects.size() > MAX_OBJECTS)
				{
					continue;
				}

				slot = chunk->allocator->alloc(sizeof(T), alignof(T));
				if (slot != nullptr)
				{
					chunk->objects.push_back((T*)slot);
					break;
				}
			}

			if (slot == nullptr)
			{
				PoolAllocator* allocator = new PoolAllocator(ALLOCATION_SIZE, allocate(ALLOCATION_SIZE, this->allocTag), sizeof(T), alignof(T));
				Chunk* newChunk = new Chunk(allocator);

				this->chunks.push_front(newChunk);
				slot = newChunk->allocator->alloc(sizeof(T), alignof(T));
				newChunk->objects.clear();
				newChunk->objects.push_back((T*)slot);

				return slot;
			}
		}

		void DestroyObject(void* object)
		{
			uintptr_t address = reinterpret_cast<uintptr_t(object);
			for (auto chunk : this->chunks)
			{
				if (chunk->chunkStart <= address && address < chunk->chunkEnd)
				{
					chunk->objects.remove((T*)object);
					chunk->allocator->free(object);
				}
			}
		}

		inline iterator begin() { return iterator(this->chunks.begin(), this->chunks.end()); }
		inline iterator end() { return iterator(this->chunks.end(), this->chunks.end()); }
	};
}