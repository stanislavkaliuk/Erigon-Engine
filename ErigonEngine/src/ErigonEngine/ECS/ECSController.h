#pragma once
#include <EECS_Controller.hpp>
#include "Components\Camera.hpp"
#include "Components\Sprite.hpp"
#include "Components\Transform.hpp"

#include "Systems\RenderSystem.h"
#include "Systems\CameraSystem.h"

ECS::EECS_Controller gECSController;

namespace ErigonEngine
{
	class ECSController
	{
	public:
		ECSController()
		{
			gECSController.Init();

			gECSController.RegisterComponent<ECS::Camera>();
			gECSController.RegisterComponent<ECS::Transform>();
			gECSController.RegisterComponent<ECS::Sprite>();

			systems = new std::vector<std::shared_ptr<::ECS::System>>();
			entities = new std::vector<::ECS::Entity>(::ECS::MAX_ENTITIES - 1);
		}

		~ECSController()
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

		void Update(float deltaTime)
		{
			for (auto sys : *systems)
			{
				sys->Update(deltaTime);
			}
		}

		template<typename T>
		T& SetupSystem(::ECS::Signature signature)
		{
			static_assert(std::is_base_of<::ECS::System, T>::value, "T must extend ::ECS::System");
			std::shared_ptr<T> t_system = gECSController.RegisterSystem<T>();
			gECSController.SetSystemSignature<T>(signature);
			systems->push_back(t_system);
			return *t_system;
		}

		template<typename T>
		T& GetSystem()
		{
			static_assert(std::is_base_of<::ECS::System, T>::value, "T must extend ::ECS::System");
			systems::iterator iter = std::find_if(systems->begin(), systems->end(), [](const std::shared_ptr<::ECS::System>& sys) { return dynamic_cast<T>(*sys) != nullptr; }
			return systems[iter];
		}

		class EntityFactory
		{
		public:
			::ECS::Entity CreateBasicEntity()
			{
				::ECS::Entity entity = gECSController.CreateEntity();
				gECSController.AddComponent(entity, ECS::Transform
					{
						glm::vec3(), glm::vec3(), glm::vec3(1,1,1)
					});
				ECSController::entities->push_back(entity);
				return entity;
			}

			::ECS::Entity CreateCamera()
			{
				::ECS::Entity entity = gECSController.CreateEntity();
				gECSController.AddComponent(entity, ECS::Transform
					{
						glm::vec3(0,0,0), glm::vec3(), glm::vec3(1,1,1)
					});
				gECSController.AddComponent(entity, ECS::Camera{});
				ECSController::entities->push_back(entity);
				return entity;
			}

			::ECS::Entity CreateSprite()
			{
				::ECS::Entity entity = gECSController.CreateEntity();
				gECSController.AddComponent(entity, ECS::Transform
					{
						glm::vec3(), glm::vec3(), glm::vec3(1,1,1)
					});
				gECSController.AddComponent(entity, ECS::Sprite{});
				ECSController::entities->push_back(entity);
				return entity;
			}
		};
		

		//Get Entity's Components Get Helpers
		//-------
		::ECS::Signature GetEntitySignatures(::ECS::Entity entity)
		{
			return gECSController.GetEntitySignatures(entity);
		}

		template<typename T>
		::ECS::ComponentType GetComponentType()
		{
			return gECSController.GetComponentType<T>();
		}
		//--------

		static ECSController* Create()
		{
			return new ECSController();
		}

	private:
		static std::vector<::ECS::Entity>* entities;
		static std::vector<std::shared_ptr<::ECS::System>>* systems;
	};
}

