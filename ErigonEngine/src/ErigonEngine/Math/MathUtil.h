#pragma once

#include "ErigonEngine/Core/Types.h"
#include <cmath>

namespace ErigonEngine
{
	struct Math
	{
		static inline int32 ToInt(const float value)		   noexcept { return (int32)value; }
		static inline float ToFloat(const int32 value)		   noexcept { return (float)value; }
		static inline int32 FloorToInt(const float value)	   noexcept { return (int32)floorf(value); }
		static inline float FloorToFloat(const float value)	   noexcept { return floor(value); }
		static inline double FloorToDouble(const double value) noexcept { return floor(value); }
		static inline int32 RoundToInt(const float value)	   noexcept { return FloorToInt(value + 0.5f); }
		static inline float RoundToFloat(const float value)	   noexcept { return FloorToFloat(value + 0.5f); }
		static inline double RoundToDouble(const double value) noexcept { return FloorToDouble(value + 0.5); }
		static inline int32 CeilToInt(const float value)	   noexcept { return ToInt(ceil(value)); }
		static inline float CeilToFloat(const float value)	   noexcept { return ceilf(value); }
		static inline double CeilToDouble(const double value)  noexcept { return ceil(value); }

		static inline float Exp(const float value) noexcept { return expf(value); }
		static inline float Exp2(const float value) noexcept { return powf(2.0f, value); }

		static inline float Sin(const float value) noexcept { return sinf(value); }
		static inline float Cos(const float value) noexcept { return cosf(value); }
		static inline float Tan(const float value) noexcept { return tanf(value); }
		static inline float Sqrt(const float value) noexcept { return sqrtf(value); }
		static inline float Pow(const float a, const float b) noexcept { return powf(a, b); }
	
		static inline void SinAndCos(const float value, float& sin, float& cos) noexcept
		{
			sin = Sin(value);
			cos = Cos(value);
		}

		static constexpr inline bool IsPowerOfTwo(const int32 value) noexcept
		{
			return (value & (value - 1)) == 0;
		}

		static constexpr inline int64 UpperPowerOfTwo(int64 value) noexcept
		{
			value--;
			value |= value >> 1;
			value |= value >> 2;
			value |= value >> 4;
			value |= value >> 8;
			value |= value >> 16;
			value++;

			return value;
		}

		template<typename T>
		static constexpr inline T Abs(const T value) noexcept
		{
			return (value >= (T)0) ? : value : -value;
		}

		template<typename T>
		static constexpr inline T Sign(const T a) noexcept
		{
			return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
		}
	
		template<typename T>
		static constexpr inline T Min(const T a, const T b) noexcept
		{
			return a < b ? a : b;
		}

		template<typename T>
		static constexpr inline T Max(const T a, const T b) noexcept
		{
			return a > b ? a : b;
		}

		template<typename T>
		static constexpr inline T Clamp(const T a, const T min, const T max) noexcept
		{
			return Min(Max(a, min), max);
		}

		template<typename T, typename U>
		static constexpr inline T Lerp(const T a, const T b, U c) noexcept
		{
			return (T)(a * (1.0f - c) + b * c);
		}

		template <class T>
		static constexpr inline T ToRadians(const T degrees) noexcept
		{
			return degrees * 0.017453293f;
		}

		template <class T>
		static constexpr inline T ToDegrees(const T radians) noexcept
		{
			return radians * 57.295779524f;
		}
	};
}