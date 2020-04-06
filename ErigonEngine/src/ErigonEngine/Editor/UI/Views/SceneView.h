#pragma once
#include "IView.h"
#include <cstdint>
#include <glm\glm.hpp>
#include <ErigonEngine\Editor\UI\EditorUIController.h>

namespace ErigonEngine
{
	namespace Editor
	{
		struct SizeSelectorData
		{
			int selectedSizeItemIndex = 0;
			const char* const items[2] = { "1280x720","1024x768" };
			const std::vector<glm::vec2> sizes = {glm::vec2(1280,720), glm::vec2(1024,768)};
			SizeSelectorData() : selectedSizeItemIndex(0)
			{}
		};

		class SceneView : public IView
		{
		public:
			virtual void Setup(void* controller) override;
			virtual void Draw() override;
			void SendCallback(const Event& event);
		private:
			void DrawMenuBar();
			void DrawSizeSelector();
			void ApplySize();


		private:
			ImGuiWindowFlags windowFlags;
			uint32_t framebufferTextureId;
			SizeSelectorData sizeSelectorData;
			void* masterController;
		};
	}
}