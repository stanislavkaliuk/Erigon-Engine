#include "TransformUI.h"

namespace Editor
{
	void TransformUI::Setup(ErigonEngine::Transform* component)
	{
		connectedComponent = component;
		treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;
	}

	void TransformUI::Draw()
	{
		if (ImGui::CollapsingHeader("Transform", treeNodeFlags))
		{
			float position[3] = { connectedComponent->position.x, connectedComponent->position.y, connectedComponent->position.z };
			if (ImGui::DragFloat3("Position", position))
			{
				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					
				}
			}
		}
	}

}