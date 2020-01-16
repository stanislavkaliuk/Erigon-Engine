#pragma once
#include "IViewUI.h"
#include "Editor\ItemInspector.h"

namespace Editor
{
	class InspectorViewUI : public IViewUI
	{
	public:
		~InspectorViewUI() { delete itemInspector; }
		virtual void Setup() override;
		virtual void Draw() override;
	private:
		ItemInspector* itemInspector;
	};
}
