#pragma once

#ifdef EECS_EXPORT
#define EECS_API __declspec(dllexport)
#else
#define EECS_API __declspec(dllimport)
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <functional>

#include <cassert>
#include <memory>

#include <string>
#include <cmath>

#include <chrono>

namespace Erigon
{
	namespace ECS
	{
		using int8 = int8_t;
		using int16 = int16_t;
		using int32 = int32_t;
		using int64 = int64_t;

		using uint8 = uint8_t;
		using uint16 = uint16_t;
		using uint32 = uint32_t;
		using uint64 = uint64_t;

		using float32 = float_t;
		using float64 = double_t;

		using intPtr = intptr_t;
		using uintPtr = uintptr_t;

		using typeID = size_t;
		using objectID = size_t;

		static const objectID INVALID_OBJ_ID = std::numeric_limits<objectID>::max();
		static const typeID INVALID_TYPE_ID = std::numeric_limits<typeID>::max();

		union TimeStamp
		{
			float32 asFloat;
			uint32 asUint;
			TimeStamp() : asUint(0U) {}
			TimeStamp(float32 floatValue) : asFloat(floatValue) {}

			operator uint32() const { return this->asUint; }

			inline const bool operator==(const TimeStamp& other) const { return this->asUint == other.asUint; }
			inline const bool operator!=(const TimeStamp& other) const { return this->asUint != other.asUint; }

			inline const bool operator>(const TimeStamp& other) const { return this->asFloat > other.asFloat; }
			inline const bool operator<(const TimeStamp& other) const { return this->asFloat < other.asFloat; }
		};
	}
}