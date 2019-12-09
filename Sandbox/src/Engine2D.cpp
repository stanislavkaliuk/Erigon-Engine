#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine2D::Engine2D() : Layer("2D Engine"), m_CameraController(1920.0f/1080.0f), EUI(new EngineUI(1920, 1080))
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
	EUI->Draw();
	EUI->DrawInspector(true, nullptr, &m_CameraController);
	EUI->DrawSceneHierarchy(true, nullptr);
}

void Engine2D::OnEvent(ErigonEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
