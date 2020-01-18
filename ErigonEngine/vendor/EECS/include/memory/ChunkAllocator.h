#pragma once
#include "allocator/PoolAllocator.h"
#include "../EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T, size_t maxObjects>
		class ChunkAllocator : protected GlobalMemoryUser
		{
			static const size_t MAX_OBJ = maxObjects;

			static const size_t ALLOC_SIZE = (sizeof(T) + alignof(T)) * MAX_OBJ;

			const char* allocTag;
		public:
			using Allocator = PoolAllocator;
			using ObjectList = std::list<T*>;

			class Chunk
			{
			public:
				Allocator* allocator;
				ObjectList objects;
				uintPtr chunkStart;
				uintPtr chunkEnd;

				Chunk(Allocator* allocator) : allocator(allocator)
				{
					this->chunkStart = reinterpret_cast<uintPtr>(allocator->GetMemoryZeroAdress());
					this->chunkEnd = this->chunkStart + ALLOC_SIZE;
					this->objects.clear();
				}
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
				Allocator* allocator = new Allocator(ALLOC_SIZE, Allocate(ALLOC_SIZE, allocTag), sizeof(T), alignof(T));
				this->chunks.push_back(new Chunk(allocator));
			}

			virtual ~ChunkAllocator()
			{
				for (Chunk* chunk : this->chunks)
				{
					for (T* obj : chunk->objects)
					{
						((T*)obj)->~T();
					}

					chunks->objects.clear();

					Free((void*)chunk->allocator->GetMemoryZeroAdress());
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
					if (chunk->objects.size() > MAX_OBJ)
					{
						continue;
					}

					slot = chunk->allocator->Allocate(sizeof(T), alignof(T));
					if (slot != nullptr)
					{
						chunk->objects.push_back((T*)slot);
						break;
					}
				}

				if (slot == nullptr)
				{
					Allocator* allocator = new Allocator(ALLOC_SIZE, Allocate(ALLOC_SIZE, this->allocTag), sizeof(T), alignof(T));
					Chunk* newChunk = new Chunk(allocator);

					this->chunks.push_front(newChunk);
					slot = newChunk->allocator->allocate(sizeof(T), alignof(T));
					newChunk->objects.Clear();
					newChunk->objects.push_back((T*)slot);
				}

				return slot;
			}

			void DestroyObject(void* object)
			{
				uintPtr addr = reinterpret_cast<uintPtr>(object);
				for (Chunk* chunk : this->chunks)
				{
					if (chunk->chunkStart <= addr && addr < chunk->chunkEnd)
					{
						chunk->objects.remove((T*)object);
						chunk->allocator->Free(object);
					}
				}
			}

			inline iterator begin() { return iterator(this->chunks.begin(), this->chunks.end()); }
			inline iterator end() { return iterator(this->chunks.end(), this->chunks.end()); }
		};
	}
}