#include "eepch.h"
#include "Sprite.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void Sprite::Setup(ErigonEngine::ECS::Sprite* component)
		{
			connectedComponent = component;
			treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;
		}

		void Sprite::Draw()
		{
			if (ImGui::CollapsingHeader("SpriteRenderer", treeNodeFlags))
			{
				
			}
		}
	}
}