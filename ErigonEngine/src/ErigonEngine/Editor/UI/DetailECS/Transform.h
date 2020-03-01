#pragma once
#include "IDetail.h"
#include "ErigonEngine\ECS\Transform.h"

namespace ErigonEngine
{
	namespace Editor
	{
		class Transform : public IDetail<ErigonEngine::Transform>
		{
		public:
			virtual void Setup(ErigonEngine::Transform* component) override;
			virtual void Draw() override;

		private:
			ImGuiTreeNodeFlags treeNodeFlags;
		};
	}
}