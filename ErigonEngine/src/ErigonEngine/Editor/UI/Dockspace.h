#pragma once
#include "IView.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class Dockspace : public IView
		{
		public:
			virtual void Setup() override;
			virtual void Draw() override;

		private:
			ImGuiWindowFlags dockWindowFlags;
			ImGuiID dockspaceId;
		};
	}
}