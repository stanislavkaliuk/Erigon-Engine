#include "eepch.h"
#include "ECSController.h"

ECS::EECS_Controller gECSController;

namespace ErigonEngine
{
	ECSController::ECSController()
	{
		gECSController.Init();

		gECSController.RegisterComponent<ECS::Camera>();
		gECSController.RegisterComponent<ECS::Transform>();
		gECSController.RegisterComponent<ECS::Sprite>();

		systems = new SystemCollection();
		entities = new std::vector<::ECS::Entity>(::ECS::MAX_ENTITIES - 1);
	}

	ECSController::~ECSController()
	{
		for (auto entity : *entities)
		{
			gECSController.DestroyEntity(entity);
		}

		delete entities;

		for (auto sys : *systems)
		{
			sys.reset();
		}

		delete systems;
	}

	void ECSController::Update(float deltaTime)
	{
		for (auto sys : *systems)
		{
			sys->Update(deltaTime);
		}
	}

	::ECS::Signature ECSController::GetEntitySignatures(::ECS::Entity entity)
	{
		return gECSController.GetEntitySignatures(entity);
	}

	ECSController* ECSController::Create()
	{
		return new ECSController();
	}

	template<typename T>
	::ECS::ComponentType ECSController::GetComponentType()
	{
		return gECSController.GetComponentType<T>();
	}

	::ECS::Entity ECSController::EntityFactory::CreateBasicEntity(ECSController& controller)
	{
		::ECS::Entity entity = gECSController.CreateEntity();
		gECSController.AddComponent(entity, ECS::Transform
			{
				glm::vec3(), glm::vec3(), glm::vec3(1,1,1)
			});
		controller.entities->push_back(entity);
		return entity;
	}

	::ECS::Entity ECSController::EntityFactory::CreateCamera(ECSController& controller)
	{
		::ECS::Entity entity = gECSController.CreateEntity();
		gECSController.AddComponent(entity, ECS::Transform
			{
				glm::vec3(0,0,0), glm::vec3(), glm::vec3(1,1,1)
			});
		gECSController.AddComponent(entity, ECS::Camera{});
		controller.entities->push_back(entity);
		return entity;
	}

	::ECS::Entity ECSController::EntityFactory::CreateSprite(ECSController& controller)
	{
		::ECS::Entity entity = gECSController.CreateEntity();
		gECSController.AddComponent(entity, ECS::Transform
			{
				glm::vec3(), glm::vec3(), glm::vec3(1,1,1)
			});
		gECSController.AddComponent(entity, ECS::Sprite{});
		controller.entities->push_back(entity);
		return entity;
	}
}