#pragma once
#include "ErigonEngine/Core/Types.h"
#include <glm/glm.hpp>

namespace ErigonEngine
{
	struct Color
	{
		char r, g, b, a;

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