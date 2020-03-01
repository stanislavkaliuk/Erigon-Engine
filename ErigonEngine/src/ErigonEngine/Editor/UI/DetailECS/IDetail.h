#pragma once
#include "imgui.h"

namespace ErigonEngine
{
	namespace Editor
	{
		template<class T>
		class IDetail
		{
		public:
			virtual void Setup(T* component) = 0;
			virtual void Draw() = 0;
		protected:
			T* connectedComponent;
		};
	}
}