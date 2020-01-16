#pragma once
#include "IViewUI.h"
#include <ErigonEngine.h>

namespace Editor
{
	class SceneViewUI : public IViewUI
	{
	public:
		virtual void Setup() override;
		virtual void Draw() override;
	private:
		uint32_t framebufferTextureId;
	};
}
