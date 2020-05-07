#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "eepch.h"

#define BIND_EVENT(x, y) std::bind(&x, y, std::placeholders::_1)

extern ECS::EECS_Controller gECSController;
extern ErigonEngine::MemoryManager* engineMemoryManager;

Engine2D::Engine2D(): Layer("2D Engine"),
						Editor(new ErigonEngine::Editor::EditorUIController(1920,1080))
{
	Editor->SetEventCallback(BIND_EVENT(Engine2D::OnEditorEvent, this));
}

void Engine2D::OnAttach()
{
	Editor->Setup(new ErigonEngine::Editor::Dockspace());
	Editor->Setup(new ErigonEngine::Editor::SceneView());

	ErigonEngine::ECSController* ecscontroller = &ErigonEngine::Application::Get().GetECSController();

	ErigonEngine::Ref<ErigonEngine::Shader> shader = ErigonEngine::Shader::Create("assets/shaders/Sprite.egl");

	ECS::Signature cameraSignature;
	cameraSignature.set(gECSController.GetComponentType<ErigonEngine::ECS::Camera>());
	cameraSignature.set(gECSController.GetComponentType<ErigonEngine::ECS::Transform>());
	cameraSystem = ecscontroller->SetupSystem<ErigonEngine::CameraSystem>(cameraSignature);
	cameraSystem->Init(glm::vec2(1280,720));

	ECS::Signature renderSignature;
	renderSignature.set(gECSController.GetComponentType<ErigonEngine::ECS::Transform>());
	renderSignature.set(gECSController.GetComponentType<ErigonEngine::ECS::Sprite>());
	renderSystem = ecscontroller->SetupSystem<ErigonEngine::RenderSystem>(renderSignature);
	renderSystem->Init(*cameraSystem);

	ErigonEngine::ECSController::EntityFactory factory = ErigonEngine::ECSController::EntityFactory();
	::ECS::Entity cameraObject = factory.CreateCamera(*ecscontroller);
	auto cameraTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(cameraObject);
	cameraTransform->position = glm::vec3(0, 0, -0.1f);
	auto cameraComponent = gECSController.GetComponent<ErigonEngine::ECS::Camera>(cameraObject);
	cameraComponent->RecalculateProjectionMatrix(glm::vec2(1280, 720));

	::ECS::Entity spriteObject = factory.CreateSprite(*ecscontroller);
	auto spriteTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(spriteObject);
	spriteTransform->position = glm::vec3(0, 0, 0.1f);
	auto spriteComponent = gECSController.GetComponent<ErigonEngine::ECS::Sprite>(spriteObject);

	auto res = ErigonEngine::Content::Content::LoadAll("textures");

	ErigonEngine::Ref<ErigonEngine::Content::IContent> texture = *res.begin();
	spriteComponent->SetShader(shader);
	spriteComponent->SetTexture(std::static_pointer_cast<ErigonEngine::Texture2D>(texture));
	spriteComponent->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	::ECS::Entity spriteObject2 = factory.CreateSprite(*ecscontroller);
	auto spriteTransform2 = gECSController.GetComponent<ErigonEngine::ECS::Transform>(spriteObject2);
	spriteTransform2->position = glm::vec3(0.5f, 0, -0.2f);
	auto spriteComponent2 = gECSController.GetComponent<ErigonEngine::ECS::Sprite>(spriteObject2);

	ErigonEngine::Ref<ErigonEngine::Content::IContent> texture2 = ErigonEngine::Content::Content::Load(std::filesystem::path("textures\\texture2.png", std::filesystem::path::format::native_format).string().c_str());
	spriteComponent2->SetShader(shader);
	spriteComponent2->SetTexture(std::static_pointer_cast<ErigonEngine::Texture2D>(texture2));
	spriteComponent2->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));
}

void Engine2D::OnDetach()
{
	delete Editor;
	cameraSystem.reset();
	renderSystem.reset();
}

void Engine2D::OnUpdate(ErigonEngine::Timestep ts)
{
	ErigonEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer2D::BeginSnap();

	ErigonEngine::RenderCommand::Clear();

	cameraSystem->Update(ts);
	renderSystem->Update(ts);
	
	ErigonEngine::Renderer2D::EndSnap();
}

void Engine2D::OnPostUpdate(ErigonEngine::Timestep ts)
{
	
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
	cameraSystem->OnEvent(e);

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
