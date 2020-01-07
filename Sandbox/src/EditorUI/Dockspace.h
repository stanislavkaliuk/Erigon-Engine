#pragma once
#include "IViewUI.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class Dockspace : public IViewUI
		{
		public:
			virtual void Setup() override;
			virtual void Draw() override;
			virtual void FinishDraw() override;
		private:
			ImGuiWindowFlags dockWindowFlags;
			ImGuiID dockspaceId;
		};
	}
}