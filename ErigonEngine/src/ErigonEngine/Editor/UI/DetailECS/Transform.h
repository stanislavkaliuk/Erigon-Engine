#pragma once
#include "IDetail.h"
#include "ErigonEngine\ECS\Components\Transform.hpp"

namespace ErigonEngine
{
	namespace Editor
	{
		class Transform : public IDetail<ErigonEngine::ECS::Transform>
		{
		public:
			virtual void Setup(ErigonEngine::ECS::Transform* component) override;
			virtual void Draw() override;

		private:
			ImGuiTreeNodeFlags treeNodeFlags;
		};
	}
}