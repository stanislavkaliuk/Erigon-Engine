#pragma once

#include "ErigonEngine/Core/Random.h"
#include "ErigonEngine/Math/MathUtil.h"

namespace ErigonEngine
{
	template <typename T>
	struct Vector2_t;

	typedef Vector2_t<float> Vector2;
	typedef Vector2_t<int> Vector2Int;

	template <typename T>
	struct Vector2_t
	{
		T x = 0;
		T y = 0;

		Vector2_t() {}
		Vector2_t(const Vector2_t& base) : x(base.x), y(base.y) {}
		Vector2_t(Vector2_t&& base) : x(base.x), y(base.y) {}
		Vector2_t(const T& scalar) : x(scalar), y(scalar) {}
		Vector2_t(const T& inX, const T& inY) : x(inX), y(inY) {}

		Vector2_t<T> XX() const { return Vector2_t<T>(x, x); }
		Vector2_t<T> XY() const { return Vector2_t<T>(x, y); }
		Vector2_t<T> YX() const { return Vector2_t<T>(y, x); }
		Vector2_t<T> YY() const { return Vector2_t<T>(y, y); }

		template <typename U>
		operator Vector2_t<U>() { return Vector2_t<U>((U)x, (U)y); }

		Vector2_t& operator=(Vector2_t& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		Vector2_t& operator=(Vector2_t&& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		Vector2_t operator+() const
		{
			return *this;
		}

		Vector2_t operator+ (const T& scalar) const
		{
			return Vector2_t(x + scalar, y + scalar);
		}

		friend Vector2_t operator+ (const T& scalar, const Vector2_t& other)
		{
			return other + scalar;
		}
		Vector2_t operator+ (const Vector2_t& other) const
		{
			return Vector2_t(x + other.x, y + other.y);
		}

		Vector2_t operator- () const
		{
			return Vector2_t(-x, -y);
		}

		Vector2_t operator-(const T& scalar) const
		{
			return Vector2_t(x - scalar, y - scalar);
		}

		friend Vector2_t operator-(const T& scalar, const Vector2_t& other)
		{
			return Vector2_t(scalar - other.x, scalar - other.y);
		}

		Vector2_t operator-(const Vector2_t& other) const
		{
			return Vector2_t(x - other.x, y - other.y);
		}

		Vector2_t operator*(const T& scalar) const
		{
			return Vector2_t(x * scalar, y * scalar);
		}

		friend Vector2_t operator*(const T& scalar, const Vector2_t& other)
		{
			return other * scalar;
		}

		Vector2_t operator*(const Vector2_t& other) const
		{
			return Vector2_t(x * other.x, y * other.y);
		}

		Vector2_t operator/(const T& scalar) const
		{
			return Vector2_t(x / scalar, y / scalar);
		}

		friend Vector2_t operator/(const T& scalar, const Vector2_t& other)
		{
			return Vector2_t(scalar / other.x, scalar / other.y);
		}

		Vector2_t operator/(const Vector2_t& other) const
		{
			return Vector2_t(x / other.x, y / other.y);
		}

		Vector2_t& operator+=(const T& scalar)
		{
			return *this = *this + scalar;
		}

		Vector2_t& operator+=(const Vector2_t& other)
		{
			return *this = *this + other;
		}

		Vector2_t& operator-=(const T& scalar)
		{
			return *this = *this - scalar;
		}

		Vector2_t& operator-=(const Vector2_t& other)
		{
			return *this = *this - other;
		}

		Vector2_t& operator*=(const T& scalar)
		{
			return *this = *this * scalar;
		}

		Vector2_t& operator*=(const Vector2_t& other)
		{
			return *this = *this * other;
		}

		Vector2_t& operator/=(const T& scalar)
		{
			return *this = *this / scalar;
		}

		Vector2_t& operator/=(const Vector2_t& other)
		{
			return *this = *this / other;
		}

		bool operator==(const Vector2_t& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vector2_t& other) const
		{
			return !(*this == other);
		}

		static Vector2_t Random(const Vector2_t& min, const Vector2_t& max)
		{
			Vector2_t result;
			result.x = SystemRandom::Range(min.x, max.x);
			result.y = SystemRandom::Range(min.y, max.y);

			return result;
		}

		Vector2_t Clamped(const Vector2_t& min, const Vector2_t& max) const
		{
			return Vector2_t(Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y));
		}

		Vector2_t& Clamp(const Vector2_t& min, const Vector2_t& max)
		{
			return *this = Clamped(min, max);
		}

		Vector2_t Normalized() const
		{
			return *this * (1.0f / sqrtf(x * x + y * y));
		}

		Vector2_t& Normalize() const
		{
			return *this = Normalized();
		}

		T Length(const Vector2_t& other) const
		{
			return sqrtf(Math::Sqr(other.x - x) + Math::Sqr(other.y - y));
		}

		T LengthSquare(const Vector2_t& other) const
		{
			return Math::Sqr(other.x - x) + Math::Sqr(other.y - y);
		}

		T Dot(const Vector2_t& other) const
		{
			return x * other.x + y * other.y;
		}
	};

}