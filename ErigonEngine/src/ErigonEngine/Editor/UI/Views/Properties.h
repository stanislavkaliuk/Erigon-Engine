#pragma once
#include "IView.h"

namespace ErigonEngine::Editor
{
	class Properties : public IView
	{
	public:
		virtual void Setup(void* controller) override;
		virtual void Draw() override;
	
	private:
		void DrawDetailContainer();
	private:
		ImGuiWindowFlags windowFlags;
		void* masterController;
	};
}
