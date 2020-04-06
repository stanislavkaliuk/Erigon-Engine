#pragma once
#include "IView.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class Dockspace : public IView
		{
		public:
			virtual void Setup(void* controller) override;
			virtual void Draw() override;
		private:
			void DrawMenuBar();
			void DrawFileMenu();
			void DrawEditMenu();
			void DrawWindowsMenu();
			void DrawHelpMenu();
			void SendCallback(const Event& event);
		private:
			ImGuiWindowFlags dockWindowFlags;
			ImGuiID dockspaceId;
			void* masterController;
		};
	}
}