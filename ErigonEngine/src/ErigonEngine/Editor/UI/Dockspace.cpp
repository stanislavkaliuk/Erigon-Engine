#include "eepch.h"
#include "Dockspace.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void Dockspace::Setup()
		{
			active = true;
			dockWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
				ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		void Dockspace::Draw()
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::Begin("Dockspace", &active, dockWindowFlags);
			dockspaceId = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockspaceId, ImVec2(0, 0), ImGuiDockNodeFlags_NoDockingInCentralNode);
			ImGui::End();
		}
	}
}

