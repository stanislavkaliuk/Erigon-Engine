#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "eepch.h"

#define BIND_EVENT(x, y) std::bind(&x, y, std::placeholders::_1)

Engine2D::Engine2D(): Layer("2D Engine"),
						Editor(new ErigonEngine::Editor::EditorUIController(1920,1080)),
						nodeEditor(new ErigonEngine::Editor::NodeEditor())
{
	Editor->SetEventCallback(BIND_EVENT(Engine2D::OnEditorEvent, this));
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

	glm::vec2 framebufferSize = ErigonEngine::Renderer2D::GetFrameBufferSize();
	ErigonEngine::Renderer2D::BeginSnap(framebufferSize.x, framebufferSize.y);

	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//ErigonEngine::Renderer2D::Draw({ 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.2f, 0.5f, 1.0f });
	//ErigonEngine::Renderer2D::Draw({ 1.5f, 1.2f }, { 0.5f, 0.5f, 1.0f }, { 0.6f, 0.4f, 0.8f, 1.0f });
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

void Engine2D::OnEvent(const ErigonEngine::Event& e)
{
	//m_CameraController.OnEvent(e);
}

void Engine2D::OnEditorEvent(const ErigonEngine::Event& e)
{
	m_CameraController.OnEvent(e);

	ErigonEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<ErigonEngine::Editor::SceneViewSizeChangedEvent>(BIND_EVENT(Engine2D::EventHandler::OnSceneViewChanged, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneCreatedEvent>(BIND_EVENT(Engine2D::EventHandler::OnSceneCreated, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneOpenedEvent>(BIND_EVENT(Engine2D::EventHandler::OnSceneOpened, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneSavedEvent>(BIND_EVENT(Engine2D::EventHandler::OnSceneSaved, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::AppExitEvent>(BIND_EVENT(Engine2D::EventHandler::OnAppExit, &eventHandler));
}

bool Engine2D::EventHandler::OnSceneViewChanged(const ErigonEngine::Editor::SceneViewSizeChangedEvent& e)
{
	auto size = e.GetSize();
	ErigonEngine::Renderer2D::RecreateFramebuffer(size.x, size.y);
	return false;
}

bool Engine2D::EventHandler::OnSceneCreated(const ErigonEngine::Editor::SceneCreatedEvent& e)
{
	return false;
}

bool Engine2D::EventHandler::OnSceneOpened(const ErigonEngine::Editor::SceneOpenedEvent& e)
{
	return false;
}

bool Engine2D::EventHandler::OnSceneSaved(const ErigonEngine::Editor::SceneSavedEvent& e)
{
	return false;
}

bool Engine2D::EventHandler::OnAppExit(const ErigonEngine::AppExitEvent& e)
{
	ErigonEngine::Application::Get().OnEvent(e);
	return true;
}
