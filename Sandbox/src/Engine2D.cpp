#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "eepch.h"

Engine2D::Engine2D() : Layer("2D Engine"), m_CameraController(1280.0f/720.0f), 
						Editor(new ErigonEngine::Editor::EditorUIController(1920,1080)),
						nodeEditor(new ErigonEngine::Editor::NodeEditor())
{
	
}

void Engine2D::OnAttach()
{
	Editor->Setup(new ErigonEngine::Editor::Dockspace());
	Editor->Setup(new ErigonEngine::Editor::SceneView());
	//nodeEditor->Attach();
	texture = ErigonEngine::Texture2D::Create("assets/textures/texture2.png");
}

void Engine2D::OnDetach()
{
	//nodeEditor->Detach();
}

void Engine2D::OnUpdate(ErigonEngine::Timestep ts)
{
	ErigonEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer2D::BeginSnap(1280, 720);

	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	ErigonEngine::Renderer2D::Draw({ 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.2f, 0.5f, 1.0f });
	ErigonEngine::Renderer2D::Draw({ 1.5f, 1.2f }, { 0.5f, 0.5f, 1.0f }, { 0.6f, 0.4f, 0.8f, 1.0f });
	//ErigonEngine::Renderer2D::Draw({ 0.0f, 0.0f, -0.1f },{ 10.0f, 10.0f, 1.0f }, texture);
	ErigonEngine::Renderer2D::EndScene();

	ErigonEngine::Renderer2D::EndSnap();
}

void Engine2D::OnPostUpdate(ErigonEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
}

void Engine2D::OnImGuiRender()
{
	Editor->Draw();
	//nodeEditor->Update();
}

void Engine2D::OnEvent(ErigonEngine::Event& e)
{
	//m_CameraController.OnEvent(e);
}
