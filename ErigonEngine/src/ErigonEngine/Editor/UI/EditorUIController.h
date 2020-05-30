#pragma once
#include "ErigonEngine\Events\Event.h"
#include "ErigonEngine\Events\EditorEvent.h"
#include <vector>
#include <functional>
#include "Views\IView.h"

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

		public:
			uint32_t windowWidth, windowHeight;
			std::vector<IView*> views;
		};
	}
}