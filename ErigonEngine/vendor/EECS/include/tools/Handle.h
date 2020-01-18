#pragma once

#include "EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		template<typename handle_value_type, size_t v_bits, size_t i_bits>
		union Handle
		{
			static_assert(sizeof(handle_value_type)* CHAR_BIT >= (v_bits + i_bits), "Handler overflow");

			using value_type = handle_value_type;

			static constexpr size_t NUM_VERSION_BITS{ v_bits };
			static constexpr size_t NUM_INDEX_BITS{ i_bits };

			static constexpr value_type MIN_VERSION{ 0 };
			static constexpr value_type MAX_VERSION{ (1U << NUM_VERSION_BITS) - 2U };
			static constexpr value_type MAX_INDICIES{ (1U << NUM_INDEX_BITS)- 2U };

			static constexpr value_type INVALID_HANDLE{ std::numeric_limits<value_type>::max() };

		private:
			value_type value;

		public:
			struct
			{
				value_type index : NUM_INDEX_BITS;
				value_type version : NUM_VERSION_BITS;
			};

			Handle() {}

			Handle(value_type value) : value(value) {}

			Handle(value_type index, value_type version) : index(index), version(version) {}

			inline operator value_type() const { return value; }
		};

		using Handle32 = Handle<uint32, 12, 20>;
		using Handle64 = Handle<uint64, 24, 40>;

		template<class T, class h_type, size_t grow = 1024>
		class HandleTable
		{
			using Handle = h_type;

		private:
			using TableEntry = std::pair<typename Handle::value_type, T*>;
			std::vector<TableEntry> table;

			void GrowTable()
			{
				size_t oldSize = this->table.size();
				size_t newSize = std::min(oldSize + grow, Handle::MAX_INDICIES);

				this->table.resize(newSize);

				for (typename Handle::value_type i = oldSize; i < newSize; ++i)
				{
					this->table[i] = TableEntry(Handle::MIN_VERSION, nullptr);
				}
			}

		public:
			HandleTable() {}
			~HandleTable() {}

			Handle AqcuireHandle(T* object)
			{
				typename Handle::value_type i = 0;
				for (; i < this->table.size(); i++)
				{
					if (this->table[i].second == nullptr)
					{
						this->table[i].second = object;
						this->table[i].first = ((this->table[i].first + 1) > Handle::MAX_VERSION) ? Handle::MIN_VERSION : this->table[i].first + 1;

						return Handle(i, this->table[i].first);
					}
				}

				this->GrowTable();
				this->table[i].first = 1;
				this->table[i].second = object;

				return Handle(i, this->table[i].first);
			}

			void ReleaseHandler(Handle handler)
			{
				this->table[handler.index].second = nullptr;
			}

			inline bool isExpired(Handle handler) const
			{
				return this->table[handler.index].first != handler.version;
			}

			inline Handle operator[](typename Handle::value_type index) const
			{
				return Handle(index, this->table[index].first);
			}

			inline T* operator[](Handle handler)
			{
				return (this->table[handler.index].first == handler.version) ? this->table[handler.index].second : nullptr;
			}
		};
	}
}