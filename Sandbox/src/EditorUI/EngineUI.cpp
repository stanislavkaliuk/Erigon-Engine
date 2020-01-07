#include "EngineUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace ErigonEngine
{
	namespace Editor
	{
		EngineUI::EngineUI(uint32_t windowWidth, uint32_t windowHeight)
		{
			this->windowWidth = windowWidth;
			this->windowHeight = windowHeight;

			views.push_back(new Dockspace());
			views.push_back(new SceneViewUI());
		}

		void EngineUI::Setup()
		{
			for (IViewUI* view : views)
			{
				view->Setup();
			}
		}

		void EngineUI::Draw()
		{
			for (IViewUI* view : views)
			{
				if (view->IsActive())
				{
					view->Draw();
				}
			}

			for (IViewUI* view : views)
			{
				if (view->IsActive())
				{
					view->FinishDraw();
				}
			}
		}
		/*
		void EngineUI::DrawInspector(bool state, ErigonEngine::OrthographicCameraController* cameraController)
		{
			//ImGui::SetNextWindowPos(ImVec2{ 1560, 0 }, ImGuiCond_Once);
			//ImGui::SetNextWindowSize(ImVec2{ 1920 - 1560, 1080 }, ImGuiCond_Once);
			ImGui::Begin("Inspector", &state, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			if (!ImGui::CollapsingHeader("Camera"))
			{
				ImGui::End();
				return;
			}

			if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				auto* camera = &(cameraController->GetCamera());
				const glm::vec3 vecPosition = camera->GetPosition();
				float position[3] = { vecPosition.x, vecPosition.y, vecPosition.z };
				float value = camera->GetRotation();
				float zoom = 1.0f / cameraController->GetZoomLevel();

				if (ImGui::DragFloat3("Position", position, 0.01f))
				{
					camera->SetTransform(glm::make_vec3(position), value);
				}

				if (ImGui::DragFloat("Rotation", &value))
				{
					camera->SetTransform(glm::make_vec3(position), value);
				}

				if (ImGui::SliderFloat("Zoom", &zoom, 0.1f, 4.0f))
				{
					cameraController->SetZoomLevel(1.0f / zoom);
					cameraController->UpdateProjection();
				}

				ImGui::TreePop();
			}

			ImGui::End();
		}

		static int selectedItem = 0;
		static const char* items[] = { "Camera", "Image1", "Image2" };

		void EngineUI::DrawSceneHierarchy(bool state)
		{
			//ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiCond_Once);
			//ImGui::SetNextWindowSize(ImVec2{ 200, 600 }, ImGuiCond_Once);
			ImGui::Begin("Scene Data", &state);
			ImGui::ListBox("", &selectedItem, items, 3);
			ImGui::End();
		}
		*/
	}
}