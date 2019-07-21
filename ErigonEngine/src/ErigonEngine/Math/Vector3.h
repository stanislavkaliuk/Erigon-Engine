#pragma once

#include <ErigonEngine/Core/Random.h>
#include <ErigonEngine/Math/Vector2.h>
#include <ErigonEngine/Math/MathUtil.h>

namespace ErigonEngine
{
	template<typename T>
	struct Vector3_t;

	typedef Vector3_t<float> Vector3;
	typedef Vector3_t<int> Vector3Int;

	template<typename T>
	struct Vector3_t
	{
		T x = 0;
		T y = 0; 
		T z = 0;

		Vector3_t() {}
		Vector3_t(const Vector3_t& base) : x(base.x), y(base.y), z(base.z) {}
		Vector3_t(const Vector3_t&& base) : x(base.x), y(base.y), z(base.z) {}
		Vector3_t(T& scalar) : x(scalar), y(scalar), z(scalar) {}
		Vector3_t(const T& newX, const T& newY,const T& newZ) : x(newX), y(newY), z(newZ) {}
		Vector3_t(const Vector2_t<T>& a, const T& b) :x(a.x), y(a.y), z(b) {}
		Vector3_t(const T& a, const Vector2<T>& b) : x(a), y(b.x), z(b.y) {}

		Vector3_t<T> XXX() const { return Vector3_t<T>(x, x, x); }
		Vector3_t<T> XXY() const { return Vector3_t<T>(x, x, y); }
		Vector3_t<T> XXZ() const { return Vector3_t<T>(x, x, z); }
		Vector3_t<T> XYX() const { return Vector3_t<T>(x, y, x); }
		Vector3_t<T> XYY() const { return Vector3_t<T>(x, y, y); }
		Vector3_t<T> XYZ() const { return Vector3_t<T>(x, y, z); }
		Vector3_t<T> XZX() const { return Vector3_t<T>(x, z, x); }
		Vector3_t<T> XZY() const { return Vector3_t<T>(x, z, y); }
		Vector3_t<T> XZZ() const { return Vector3_t<T>(x, z, z); }
		Vector3_t<T> YXX() const { return Vector3_t<T>(y, x, x); }
		Vector3_t<T> YXY() const { return Vector3_t<T>(y, x, y); }
		Vector3_t<T> YXZ() const { return Vector3_t<T>(y, x, z); }
		Vector3_t<T> YYX() const { return Vector3_t<T>(y, y, x); }
		Vector3_t<T> YYY() const { return Vector3_t<T>(y, y, y); }
		Vector3_t<T> YYZ() const { return Vector3_t<T>(y, y, z); }
		Vector3_t<T> YZX() const { return Vector3_t<T>(y, z, x); }
		Vector3_t<T> YZY() const { return Vector3_t<T>(y, z, y); }
		Vector3_t<T> YZZ() const { return Vector3_t<T>(y, z, z); }
		Vector3_t<T> ZXX() const { return Vector3_t<T>(z, x, x); }
		Vector3_t<T> ZXY() const { return Vector3_t<T>(z, x, y); }
		Vector3_t<T> ZXZ() const { return Vector3_t<T>(z, x, z); }
		Vector3_t<T> ZYX() const { return Vector3_t<T>(z, y, x); }
		Vector3_t<T> ZYY() const { return Vector3_t<T>(z, y, y); }
		Vector3_t<T> ZYZ() const { return Vector3_t<T>(z, y, z); }
		Vector3_t<T> ZZX() const { return Vector3_t<T>(z, z, x); }
		Vector3_t<T> ZZY() const { return Vector3_t<T>(z, z, y); }
		Vector3_t<T> ZZZ() const { return Vector3_t<T>(z, z, z); }

		template <typename U>
		operator Vector3_t<U>() { return Vector3_t<U>((U)x, (U)y, (U)z); }

		Vector3_t& operator=(Vector3_t& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		Vector3_t& operator=(Vector3_t&& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		Vector3_t operator+() const
		{
			return *this;
		}

		Vector3_t operator+ (const T& scalar) const
		{
			return Vector3_t(x + scalar, y + scalar, z + scalar);
		}

		friend Vector3_t operator+ (const T& scalar, const Vector3_t& other)
		{
			return other + scalar;
		}
		Vector3_t operator+ (const Vector3_t& other) const
		{
			return Vector3_t(x + other.x, y + other.y, z + other.z );
		}

		Vector3_t operator- () const
		{
			return Vector3_t(-x, -y, -z);
		}

		Vector3_t operator-(const T& scalar) const
		{
			return Vector3_t(x - scalar, y - scalar, z - scalar);
		}

		friend Vector3_t operator-(const T& scalar, const Vector3_t& other)
		{
			return Vector3_t(scalar - other.x, scalar - other.y, scalar - other.z);
		}

		Vector3_t operator-(const Vector3_t& other) const
		{
			return Vector3_t(x - other.x, y - other.y, z - other.z);
		}

		Vector3_t operator*(const T& scalar) const
		{
			return Vector3_t(x * scalar, y * scalar, z * scalar);
		}

		friend Vector3_t operator*(const T& scalar, const Vector3_t& other)
		{
			return other * scalar;
		}

		Vector3_t operator*(const Vector3_t& other) const
		{
			return Vector3_t(x * other.x, y * other.y, z *other.z);
		}

		Vector3_t operator/(const T& scalar) const
		{
			return Vector3_t(x / scalar, y / scalar, z/scalar);
		}

		friend Vector3_t operator/(const T& scalar, const Vector3_t& other)
		{
			return Vector3_t(scalar / other.x, scalar / other.y, scalar/other.y);
		}

		Vector3_t operator/(const Vector3_t& other) const
		{
			return Vector3_t(x / other.x, y / other.y, z / other.z);
		}

		Vector3_t& operator+=(const T& scalar)
		{
			return *this = *this + scalar;
		}

		Vector3_t& operator+=(const Vector3_t& other)
		{
			return *this = *this + other;
		}

		Vector3_t& operator-=(const T& scalar)
		{
			return *this = *this - scalar;
		}

		Vector3_t& operator-=(const Vector3_t& other)
		{
			return *this = *this - other;
		}

		Vector3_t& operator*=(const T& scalar)
		{
			return *this = *this * scalar;
		}

		Vector3_t& operator*=(const Vector3_t& other)
		{
			return *this = *this * other;
		}

		Vector3_t& operator/=(const T& scalar)
		{
			return *this = *this / scalar;
		}

		Vector3_t& operator/=(const Vector3_t& other)
		{
			return *this = *this / other;
		}

		bool operator==(const Vector3_t& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const Vector3_t& other) const
		{
			return !(*this == other);
		}

		static Vector3_t Random(const Vector3_t& min, const Vector3_t& max)
		{
			Vector3_t result;
			result.x = SystemRandom::Range(min.x, max.x);
			result.y = SystemRandom::Range(min.y, max.y);
			result.z = SystemRandom::Range(min.z, max.z);

			return result;
		}

		static Vector3_t Clamp(const Vector3_t& a, const Vector3_t& min, const Vector3_t& max)
		{
			return Vector3_t(Math::Clamp(a.x, min.x, max.x), Math::Clamp(a.y, min.y, max.x), Math::Clamp(a.z, min.z, max.z));
		}

		static Vector3_t Normalize(const Vector3_t& other)
		{
			return other * (1.0f / sqrt(other.x * other.x + other.y * other.y + other.z * other.z));
		}

		static T Dot(const Vector3_t& a, const Vector3_t& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		static Vector3_t Cross(const Vector3_t& a, const Vector3_t& b)
		{
			return Vector3_t(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		}

		Vector3_t Clamped(const Vector3_t& min, const Vector3_t& max) const
		{
			return Vector3_t(Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z));
		}

		Vector3_t& Clamp(const Vector3_t& min, const Vector3_t& max)
		{
			return *this = Clamped(min, max);
		}

		Vector3_t Normalized() const
		{
			return *this * (1.0f / sqrtf(x * x + y * y + z * z));
		}

		Vector3_t& Normalize()
		{
			return *this = Normalized();
		}

		T Length(const Vector3_t& other) const
		{
			return sqrtf(Math::Sqr(other.x - x) + Math::Sqr(other.y - y) + Math::Sqr(other.z - z));
		}

		T LengthSquare(const Vector3_t& other) const
		{
			return Math::Sqr(other.x - x) + Math::Sqr(other.y - y) + Math::Sqr(other.z - z);
		}

		T Dot(const Vector3_t& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vector3_t Cross(const Vector3_t& other) const
		{
			return Vector3_t(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
		}
	};
}