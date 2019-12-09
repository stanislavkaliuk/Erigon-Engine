#include "EngineUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

EngineUI::EngineUI(uint32_t windowWidth, uint32_t windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	results = new TransformResult[2];
	RecalculateTransforms(results);
}

void EngineUI::Draw()
{

}

void EngineUI::DrawInspector(bool state, UITransform* transform, ErigonEngine::OrthographicCameraController* cameraController)
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
		auto *camera = &(cameraController->GetCamera());
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
			cameraController->SetZoomLevel(1.0f/zoom);
			cameraController->UpdateProjection();
		}

		ImGui::TreePop();
	}
	
	ImGui::End();
}
	static int selectedItem = 0;
	static const char* items[] = { "Camera", "Image1", "Image2" };

void EngineUI::DrawSceneHierarchy(bool state, UITransform* transform)
{
	//ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiCond_Once);
	//ImGui::SetNextWindowSize(ImVec2{ 200, 600 }, ImGuiCond_Once);
	ImGui::Begin("Scene Data", &state, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::Columns(1, "SceneDataColumn", true);
	for (int i = 0; i < 3; i++)
	{
		if (ImGui::Selectable(items[i]))
		{

		}
	}
	ImGui::End();

}


void EngineUI::RecalculateTransforms(TransformResult* results)
{
	ImVec2 basicSizeRatio = { 1, 3 };	

	TransformResult* inspectorData = &results[0];

	inspectorData->target = TransformTarget::Inspector;

	UITransform inspectorTransform = {};
	inspectorTransform.size = { windowHeight / basicSizeRatio.y, windowHeight * basicSizeRatio.x };

	inspectorData->transform = inspectorTransform;

	TransformResult* hierarchyData = &results[1];

	hierarchyData->target = TransformTarget::Hierarchy;

	UITransform hierarchyTransform = {};
	hierarchyTransform.size = { (windowHeight / basicSizeRatio.y) * 0.75f, windowHeight / 1.8f };

	hierarchyData->transform = hierarchyTransform;

}