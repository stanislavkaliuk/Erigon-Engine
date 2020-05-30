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
}

void Engine2D::OnAttach()
{
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
	::ECS::Entity cameraEntity = factory.CreateCamera(*ecscontroller);
	auto cameraTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(cameraEntity);
	cameraTransform->position = glm::vec3(0, 0, 0.0f);
	auto cameraComponent = gECSController.GetComponent<ErigonEngine::ECS::Camera>(cameraEntity);
	cameraComponent->RecalculateProjectionMatrix(glm::vec2(1280, 720));
	
	cameraObject = new ErigonEngine::GameObject(cameraEntity, {cameraTransform, cameraComponent});

	::ECS::Entity spriteEntity = factory.CreateSprite(*ecscontroller);
	auto spriteTransform = gECSController.GetComponent<ErigonEngine::ECS::Transform>(spriteEntity);
	spriteTransform->position = glm::vec3(0, 0, 0.1f);
	auto spriteComponent = gECSController.GetComponent<ErigonEngine::ECS::Sprite>(spriteEntity);

	sprite1Object = new ErigonEngine::GameObject(spriteEntity, { spriteTransform, spriteComponent });

	auto res = ErigonEngine::Content::Content::LoadAll("textures");

	ErigonEngine::Ref<ErigonEngine::Content::IContent> texture = *res.begin();
	spriteComponent->SetShader(shader);
	spriteComponent->SetTexture(std::static_pointer_cast<ErigonEngine::Texture2D>(texture));
	spriteComponent->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	::ECS::Entity spriteObject2 = factory.CreateSprite(*ecscontroller);
	auto spriteTransform2 = gECSController.GetComponent<ErigonEngine::ECS::Transform>(spriteObject2);
	spriteTransform2->position = glm::vec3(0.8f, 0, 0.0f);
	auto spriteComponent2 = gECSController.GetComponent<ErigonEngine::ECS::Sprite>(spriteObject2);

	ErigonEngine::Ref<ErigonEngine::Content::IContent> texture2 = ErigonEngine::Content::Content::Load(std::filesystem::path("textures\\texture2.png", std::filesystem::path::format::native_format).string().c_str());
	spriteComponent2->SetShader(shader);
	spriteComponent2->SetTexture(std::static_pointer_cast<ErigonEngine::Texture2D>(texture2));
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
