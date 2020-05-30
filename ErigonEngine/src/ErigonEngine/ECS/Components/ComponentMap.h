#pragma once
#include "ErigonEngine/Core/Core.h"
#include <EECS_Controller.hpp>

namespace ErigonEngine
{
	namespace ECS
	{
		enum class ComponentMap
		{
			Transform = 0x0000,
			Camera = 0x0001,
			Sprite = 0x0002
		};

		static ComponentMap ToComponentMap(::ECS::ComponentType type)
		{
			return (ComponentMap)type;
		}
	}
}