#include "eepch.h"
#include "EditorUIController.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void EditorUIController::Setup(IView* view)
		{
			views.push_back(view);
			view->Setup();
		}

		void EditorUIController::Draw()
		{
			for(IView* view : views)
			{
				if (view->IsActive())
				{
					view->Draw();
				}
			}
		}
	}
}

