#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Engine2D::Engine2D() : Layer("2D Engine"), m_CameraController(1280.0f/720.0f)
{

}

void Engine2D::OnAttach()
{
	texture = ErigonEngine::Texture2D::Create("assets/textures/texture2.png");
}

void Engine2D::OnDetach()
{

}

void Engine2D::OnUpdate(ErigonEngine::Timestep ts)
{

	ErigonEngine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	ErigonEngine::Renderer2D::Draw({ 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.2f, 0.5f, 1.0f });
	ErigonEngine::Renderer2D::Draw({ 1.5f, 1.2f }, { 0.5f, 0.5f, 1.0f }, { 0.6f, 0.4f, 0.8f, 1.0f });
	ErigonEngine::Renderer2D::Draw({ 0.0f, 0.0f, -0.1f },{ 10.0f, 10.0f, 1.0f }, texture);
	ErigonEngine::Renderer2D::EndScene();
}

void Engine2D::OnPostUpdate(ErigonEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
}

void Engine2D::OnImGuiRender()
{
	bool open = true;
	ImGui::SetNextWindowPos(ImVec2{ 1024, 0 }, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2{ 1280 - 1024, 450 }, ImGuiCond_Always);
	ImGui::Begin("Inspector", &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if (!ImGui::CollapsingHeader("Camera"))
	{
		ImGui::End();
		return;
	}

	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto camera = m_CameraController.GetCamera();
		const glm::vec3 vecPosition = camera.GetPosition();
		float position[3] = { vecPosition.x, vecPosition.y, vecPosition.z };
		float value = camera.GetRotation();
		float zoom = m_CameraController.GetZoomLevel();

		if (ImGui::DragFloat3("Position", position, 0.01f))
		{
			m_CameraController.GetCamera().SetTransform(glm::make_vec3(position), value);
		}

		if (ImGui::DragFloat("Rotation", &value))
		{
			m_CameraController.GetCamera().SetTransform(glm::make_vec3(position), value);
		}

		if (ImGui::SliderFloat("Zoom", &zoom, 0.25f, 5.0f))
		{
			m_CameraController.SetZoomLevel(zoom);
			m_CameraController.UpdateProjection();
		}

		ImGui::TreePop();
	}
	
	ImGui::End();
}

void Engine2D::OnEvent(ErigonEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
