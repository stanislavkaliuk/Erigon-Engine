#include "eepch.h"
#include "Transform.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void Transform::Setup(ErigonEngine::Transform* component)
		{
			connectedComponent = component;
			treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;
		}

		void Transform::Draw()
		{
			if (ImGui::CollapsingHeader("Transform", treeNodeFlags))
			{
				float* position = connectedComponent->position.GetUnpacked();
				if(ImGui::DragFloat3("Position", position))
				{
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						connectedComponent->position = position;
					}
				}

				float* scale = connectedComponent->scale.GetUnpacked();
				if (ImGui::DragFloat3("Scale", scale))
				{
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						connectedComponent->scale = scale;
					}
				}
			}
		}
	}
}

