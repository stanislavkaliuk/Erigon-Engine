#include "Engine2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "eepch.h"


extern ECS::EECS_Controller gECSController;
extern ErigonEngine::MemoryManager* engineMemoryManager;

#define BIND_EVENT(x, y) std::bind(&x, y, std::placeholders::_1)

Engine2D::Engine2D(): Layer("2D Engine")
{
	ErigonEngine::EventManager::AddListener(ErigonEngine::Editor::SceneViewSizeChangedEvent::GetStaticType(), BIND_EVENT(Engine2D::OnEditorEvent, this));
	ErigonEngine::EventManager::AddListener(ErigonEngine::Editor::SceneSavedEvent::GetStaticType(), BIND_EVENT(Engine2D::OnEditorEvent, this));
}

void Engine2D::OnAttach()
{
	ErigonEngine::ECSController* ecscontroller = &ErigonEngine::Application::Get().GetECSController();


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

	scene = new ErigonEngine::Scene();


	ErigonEngine::ECSController::EntityFactory factory = ErigonEngine::ECSController::EntityFactory(ecscontroller);
	
	AddCamera(ecscontroller, factory, glm::vec2(1280, 720));

	AddSprite(ecscontroller, factory, { 0.0f, 0.0f, 0.1f }, "textures\\texture2.png");

	AddSprite(ecscontroller, factory, { 0.5f, 0.0f, 0.0f }, "textures\\Icon.png");
}

void Engine2D::OnDetach()
{
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
	//ImGui::ShowDemoWindow();
	//nodeEditor->Update();
}

void Engine2D::OnEvent(const ErigonEngine::Event& e)
{
	//m_CameraController.OnEvent(e);
}

void Engine2D::OnEditorEvent(const ErigonEngine::Event& e)
{
	cameraSystem->OnEvent(e);

}

void Engine2D::AddCamera(ErigonEngine::ECSController* controller, ErigonEngine::ECSController::EntityFactory& factory, glm::vec2 resolution)
{
	::ECS::Entity cameraEntity = factory.CreateCamera();
	auto cameraTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(cameraEntity);
	cameraTransform->position = glm::vec3(0, 0, 0.0f);
	auto cameraComponent = gECSController.GetComponent<ErigonEngine::ECS::Camera>(cameraEntity);
	cameraComponent->RecalculateProjectionMatrix(resolution);
	scene->Add(new ErigonEngine::GameObject(cameraEntity, controller->GetEntitySignatures(cameraEntity), { cameraTransform, cameraComponent }));
}

void Engine2D::AddSprite(ErigonEngine::ECSController* controller, ErigonEngine::ECSController::EntityFactory& factory, glm::vec3 pos, const char* path, glm::vec3 color)
{
	ErigonEngine::Ref<ErigonEngine::Shader> shader = ErigonEngine::Shader::Create("assets/shaders/Sprite.egl");

	::ECS::Entity spriteObject = factory.CreateSprite();
	auto spriteTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(spriteObject);
	{
		spriteTransform->position = { pos.x, pos.y,-pos.z };
	}
	auto spriteComponent = gECSController.GetComponent<ErigonEngine::ECS::Sprite>(spriteObject);
	{
		ErigonEngine::Ref<ErigonEngine::Content::IContent> texture2 = ErigonEngine::Content::Content::Load(std::filesystem::path(path, std::filesystem::path::format::native_format).string().c_str());
		spriteComponent->SetShader(shader);
		spriteComponent->SetTexture(std::static_pointer_cast<ErigonEngine::Texture2D>(texture2));
		spriteComponent->SetColor(color);
	}
	scene->Add(new ErigonEngine::GameObject(spriteObject, controller->GetEntitySignatures(spriteObject), { spriteTransform, spriteComponent }));
}
