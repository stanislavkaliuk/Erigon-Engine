#pragma once
#include "IView.h"
#include <cstdint>

namespace ErigonEngine
{
	namespace Editor
	{
		struct SizeSelectorData
		{
			int selectedSizeItemIndex = 0;
			const char* const items[2] = { "1280x720","1024x768" };
			SizeSelectorData() : selectedSizeItemIndex(0)
			{}
		};

		class SceneView : public IView
		{
		public:
			virtual void Setup() override;
			virtual void Draw() override;
		private:
			void DrawMenuBar();
			void DrawSizeSelector();
		private:
			ImGuiWindowFlags windowFlags;
			uint32_t framebufferTextureId;
			SizeSelectorData sizeSelectorData;
		};
	}
}