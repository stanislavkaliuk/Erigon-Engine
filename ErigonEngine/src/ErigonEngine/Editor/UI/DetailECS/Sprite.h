#pragma once
#include "IDetail.h"
#include "ErigonEngine\ECS\Sprite.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class Sprite : public IDetail<ErigonEngine::Sprite>
		{
		public:
			virtual void Setup(ErigonEngine::Sprite* component) override;
			virtual void Draw() override;
		private:
			ImGuiTreeNodeFlags treeNodeFlags;
		};
	}
}