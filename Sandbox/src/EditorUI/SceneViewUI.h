#pragma once
#include "IViewUI.h"
#include "ErigonEngine.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class SceneViewUI : public IViewUI
		{
		public:
			virtual void Setup() override;
			virtual void Draw() override;
		private:
			uint32 framebufferTextureId;
		};
	}
}