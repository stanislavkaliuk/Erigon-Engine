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

		for (SystemCollection::iterator it = systems->begin(); it != systems->end(); it++)
		{
			it->reset();
		}

		delete systems;
	}

	void ECSController::Update(float deltaTime)
	{
		for (SystemCollection::iterator it = systems->begin(); it != systems->end(); it++)
		{
			it->get()->Update(deltaTime);
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
		gECSController.AddComponent(entity, ECS::Camera());
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
		ECS::Sprite sprite = ECS::Sprite();
		sprite.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		gECSController.AddComponent(entity, sprite);
		controller.entities->push_back(entity);
		return entity;
	}
}