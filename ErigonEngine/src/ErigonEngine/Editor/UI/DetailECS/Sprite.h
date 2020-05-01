#pragma once
#include "IDetail.h"
#include "ErigonEngine\ECS\Components\Sprite.hpp"

namespace ErigonEngine
{
	namespace Editor
	{
		class Sprite : public IDetail<ErigonEngine::ECS::Sprite>
		{
		public:
			virtual void Setup(ErigonEngine::ECS::Sprite* component) override;
			virtual void Draw() override;
		private:
			ImGuiTreeNodeFlags treeNodeFlags;
		};
	}
}