#pragma once
#include "IViewUI.h"

namespace Editor
{
	class Dockspace : public IViewUI
	{
	public:
		virtual void Setup() override;
		virtual void Draw() override;
	private:
		ImGuiWindowFlags dockWindowFlags;
		ImGuiID dockspaceId;
	};
}