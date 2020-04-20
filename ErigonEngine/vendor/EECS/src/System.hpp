#pragma once
#include "Types.hpp"
#include <set>

namespace ECS
{
	class System
	{
	public:
		virtual void Init() {}
		virtual void Update(float deltaTime){}
		std::set<Entity> entities;
	};
}