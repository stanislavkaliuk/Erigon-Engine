#pragma once
#include "IComponentUI.h"
#include "ErigonEngine\ECS\Transform.h"

namespace Editor
{
	class TransformUI : public IComponentUI<ErigonEngine::Transform>
	{
	public:
		virtual void Setup(ErigonEngine::Transform* component) override;
		virtual void Draw() override;
	private:
		ImGuiTreeNodeFlags treeNodeFlags;
	};
}
