#pragma once
#include "IView.h"
#include <vector>

namespace ErigonEngine
{
	namespace Editor
	{
		class EditorUIController
		{
		public:
			EditorUIController(uint32_t width, uint32_t height) : windowWidth(width), windowHeight(height) 
			{
			}

			void Setup(IView* view);
			void Draw();

			IView* GetView(ViewType viewType);

			uint32_t windowWidth, windowHeight;
			std::vector<IView*> views;
		};
	}
}