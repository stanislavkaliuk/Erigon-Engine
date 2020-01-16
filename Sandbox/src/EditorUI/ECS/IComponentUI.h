#pragma once
#include "ErigonEngine\ECS\IComponent.h"
#include <imgui\imgui.h>

namespace Editor
{
	template<class T>
	class IComponentUI
	{
	public:
		virtual void Setup(T* component) = 0;
		virtual void Draw() = 0;
	protected:
		T* connectedComponent;
	};
}
