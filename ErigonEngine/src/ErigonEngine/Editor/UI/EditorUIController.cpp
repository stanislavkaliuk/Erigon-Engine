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

		IView* EditorUIController::GetView(ViewType viewType)
		{
			for (IView* view : views)
			{
				if (view->GetViewType() == viewType)
				{
					return view;
				}
			}

			return nullptr;
		}
	}
}

