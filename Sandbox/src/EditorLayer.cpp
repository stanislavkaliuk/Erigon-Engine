#include "EditorLayer.h"

#define BIND_EVENT(x, y) std::bind(&x, y, std::placeholders::_1)

EditorLayer::EditorLayer() : Layer("Engine Editor"), Editor(new ErigonEngine::Editor::EditorUIController(1920, 1080))
{
	using namespace ErigonEngine;
	EventManager::AddListener(Editor::SceneViewSizeChangedEvent::GetStaticType(), BIND_EVENT(EditorLayer::OnEditorEvent, this));
	EventManager::AddListener(Editor::SceneCreatedEvent::GetStaticType(), BIND_EVENT(EditorLayer::OnEditorEvent, this));
	EventManager::AddListener(Editor::SceneOpenedEvent::GetStaticType(), BIND_EVENT(EditorLayer::OnEditorEvent, this));
	EventManager::AddListener(Editor::SceneSavedEvent::GetStaticType(), BIND_EVENT(EditorLayer::OnEditorEvent, this));
}

void EditorLayer::OnAttach()
{
	Editor->Setup(new ErigonEngine::Editor::Dockspace());
	Editor->Setup(new ErigonEngine::Editor::SceneView());
	Editor->Setup(new ErigonEngine::Editor::Properties());
}

void EditorLayer::OnDetach()
{
	delete Editor;
}

void EditorLayer::OnUpdate(ErigonEngine::Timestep ts)
{
}

void EditorLayer::OnPostUpdate(ErigonEngine::Timestep ts)
{
}

void EditorLayer::OnImGuiRender()
{
	Editor->Draw();
}

void EditorLayer::OnEvent(const ErigonEngine::Event& e)
{
}

void EditorLayer::OnEditorEvent(const ErigonEngine::Event& e)
{
	ErigonEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<ErigonEngine::Editor::SceneViewSizeChangedEvent>(BIND_EVENT(EditorLayer::EventHandler::OnSceneViewChanged, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneCreatedEvent>(BIND_EVENT(EditorLayer::EventHandler::OnSceneCreated, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneOpenedEvent>(BIND_EVENT(EditorLayer::EventHandler::OnSceneOpened, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::Editor::SceneSavedEvent>(BIND_EVENT(EditorLayer::EventHandler::OnSceneSaved, &eventHandler));
	dispatcher.Dispatch<ErigonEngine::AppExitEvent>(BIND_EVENT(EditorLayer::EventHandler::OnAppExit, &eventHandler));
}

bool EditorLayer::EventHandler::OnSceneViewChanged(const ErigonEngine::Editor::SceneViewSizeChangedEvent& e)
{
	auto size = e.GetSize();
	ErigonEngine::Renderer2D::RecreateFramebuffer(size.x, size.y);
	return false;
}

bool EditorLayer::EventHandler::OnSceneCreated(const ErigonEngine::Editor::SceneCreatedEvent& e)
{
	return false;
}

bool EditorLayer::EventHandler::OnSceneOpened(const ErigonEngine::Editor::SceneOpenedEvent& e)
{
	return false;
}

bool EditorLayer::EventHandler::OnSceneSaved(const ErigonEngine::Editor::SceneSavedEvent& e)
{
	return false;
}

bool EditorLayer::EventHandler::OnAppExit(const ErigonEngine::AppExitEvent& e)
{
	ErigonEngine::Application::Get().OnEvent(e);
	return true;
}
