#pragma once
#include "ErigonEngine.h"
#include "ErigonEngine\Editor\UI\Editor.h"
#include "ErigonEngine\Events\Event.h"
#include "ErigonEngine\Editor\UI\NodeEditor\NodeEditor.h"

class Engine2D : public ErigonEngine::Layer
{
public:
	Engine2D();
	virtual ~Engine2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ErigonEngine::Timestep ts) override;
	void OnPostUpdate(ErigonEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(const ErigonEngine::Event& e) override;
	void OnEditorEvent(const ErigonEngine::Event& e);

	//Event Handling
	class EventHandler
	{
	public:
		bool OnSceneViewChanged(const ErigonEngine::Editor::SceneViewSizeChangedEvent& e);
		bool OnSceneCreated(const ErigonEngine::Editor::SceneCreatedEvent& e);
		bool OnSceneOpened(const ErigonEngine::Editor::SceneOpenedEvent& e);
		bool OnSceneSaved(const ErigonEngine::Editor::SceneSavedEvent& e);
		bool OnAppExit(const ErigonEngine::AppExitEvent& e);
	};

private:
	EventHandler eventHandler;
	ErigonEngine::Editor::EditorUIController* Editor;
	
	//ECS
	std::shared_ptr<ErigonEngine::CameraSystem> cameraSystem;
	std::shared_ptr<ErigonEngine::RenderSystem> renderSystem;

};