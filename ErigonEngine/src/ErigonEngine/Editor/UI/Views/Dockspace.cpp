#include "eepch.h"
#include "Dockspace.h"
#include "../EditorUIController.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void Dockspace::Setup(void* controller)
		{
			active = true;
			dockWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
				ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			viewType = ViewType::Other;
			masterController = controller;
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
			DrawMenuBar();
			ImGui::End();
		}

		void Dockspace::DrawMenuBar()
		{
			if (ImGui::BeginMenuBar())
			{
				DrawFileMenu();
				DrawEditMenu();
				DrawWindowsMenu();
				DrawHelpMenu();
			}
			ImGui::EndMenuBar();
		}

		void Dockspace::DrawFileMenu()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene"))
				{
					SceneCreatedEvent event;
					SendCallback(event);
				}
				if (ImGui::MenuItem("Open Scene"))
				{
					SceneOpenedEvent event;
					SendCallback(event);
				}
				if (ImGui::MenuItem("Save Scene"))
				{
					SceneSavedEvent event;
					SendCallback(event);
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
				{
					AppExitEvent event;
					SendCallback(event);
				}
				ImGui::EndMenu();
			}
		}

		void Dockspace::DrawEditMenu()
		{
			if(ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}
		}

		void Dockspace::DrawWindowsMenu()
		{
			if (ImGui::BeginMenu("Window"))
			{
				ImGui::EndMenu();
			}
		}

		void Dockspace::DrawHelpMenu()
		{
			if (ImGui::BeginMenu("Help"))
			{
				ImGui::MenuItem("About");
				ImGui::EndMenu();
			}
		}

		void Dockspace::SendCallback(const Event& event)
		{
			EventManager::InvokeEvent(event.GetEventType(), const_cast<Event&>(event));
		}
	}
}

