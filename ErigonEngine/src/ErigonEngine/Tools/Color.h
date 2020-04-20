#pragma once
#include "ErigonEngine/Core/Types.h"
#include <glm/glm.hpp>

namespace ErigonEngine
{
	struct Color
	{
		char r, g, b, a;

		Color()
		{
			this->r = 255;
			this->g = 255;
			this->b = 255;
			this->a = 255;
		}

		Color(char r, char g, char b, char a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		Color(char r, char g, char b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = 255;
		}

		uint32 GetHexValue()
		{
			return (r << 24) | (g << 16) | (b << 8) | a;
		}

		Color& operator=(const glm::vec4& color)
		{
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;

			return *this;
		}

		Color& operator=(const glm::vec3& color)
		{
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = 1.0f;

			return *this;
		}

		operator glm::vec4() const
		{
			glm::vec4 v;
			v.r = this->r;
			v.g = this->g;
			v.b = this->b;
			v.a = this->a;
			return v;
		}

		operator glm::vec3() const
		{
			glm::vec3 v;
			v.r = this->r;
			v.g = this->g;
			v.b = this->b;
			return v;
		}
	};
}