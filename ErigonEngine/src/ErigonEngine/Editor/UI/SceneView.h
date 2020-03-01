#pragma once
#include "IView.h"
#include <cstdint>

namespace ErigonEngine
{
	namespace Editor
	{
		class SceneView : public IView
		{
		public:
			virtual void Setup() override;
			virtual void Draw() override;
		private:
			ImGuiWindowFlags windowFlags;
			uint32_t framebufferTextureId;
		};
	}
}