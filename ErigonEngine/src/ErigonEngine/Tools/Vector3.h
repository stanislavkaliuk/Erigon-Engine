#pragma once
#include <glm/glm.hpp>
#include "ErigonEngine/Log/Log.h"

namespace ErigonEngine
{
	struct Vector3
	{
		float x, y, z;

		Vector3(glm::vec2 position)
		{
			x = position.x;
			y = position.y;
			z = 0;
		}

		Vector3(glm::vec3 position)
		{
			x = position.x;
			y = position.y;
			z = position.z;
		}

		Vector3(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
		}

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

	public:
		static Vector3 Zero()
		{
			return Vector3(0,0);
		}

		static Vector3 One()
		{
			return Vector3(1, 1, 1);
		}

		static Vector3 Right()
		{
			return Vector3(1, 0, 0);
		}

		static Vector3 Left()
		{
			return Vector3(-1, 0, 0);
		}

		static Vector3 Up()
		{
			return Vector3(0, 1, 0);
		}

		static Vector3 Down()
		{
			return Vector3(0, -1, 0);
		}

		//TODO: Add functions for vectors there

		Vector3& operator+=(const Vector3& b)
		{
			x += b.x;
			y += b.y;
			z += b.z;

			return *this;
		}

		Vector3& operator-=(const Vector3& b)
		{
			x -= b.x;
			y -= b.y;
			z -= b.z;

			return *this;
		}

		Vector3 operator+(Vector3& b)
		{
			Vector3 a (*this);
			a += b;
			return a;
		}

		Vector3 operator-(Vector3& b)
		{
			Vector3 a (*this);
			a -= b;
			return a;
		}

		Vector3 operator*(float d)
		{
			x *= d;
			y *= d;
			z *= d;

			return *this;
		}

		Vector3 operator/(float d)
		{

			if (d == 0)
			{
				EE_ERROR("Can't divide Vector3 to zero. Terminate operation");
				return *this;
			}

			x /= d;
			y /= d;
			z /= d;

			return *this;
		}

		bool operator==(const Vector3& b)
		{
			return x == b.x && y == b.y && z == b.z;
		}

		bool operator!=(const Vector3& b)
		{
			return x != b.x || y != b.y || z != b.z;
		}
	};
}
