#pragma once
#include <EECS_Controller.hpp>
#include "Components\Camera.hpp"
#include "Components\Sprite.hpp"
#include "Components\Transform.hpp"

#include "Systems\RenderSystem.h"
#include "Systems\CameraSystem.h"

namespace ErigonEngine
{
	using SystemCollection = std::vector<std::shared_ptr<::ECS::System>>;
	
	class ECSController
	{
	public:
		ECSController();
		~ECSController();
		void Update(float deltaTime);

		template<typename T>
		std::shared_ptr<T> SetupSystem(::ECS::Signature signature)
		{
			std::shared_ptr<T> t_system = gECSController.RegisterSystem<T>();
			gECSController.SetSystemSignature<T>(signature);
			systems->push_back(t_system);
			return t_system;
		}
		
		class EntityFactory
		{
			friend class ECSController;
		public:

			::ECS::Entity CreateBasicEntity(ECSController& controller);

			::ECS::Entity CreateCamera(ECSController& controller);

			::ECS::Entity CreateSprite(ECSController& controller);
		};
		

		//Get Entity's Components Get Helpers
		//-------
		::ECS::Signature GetEntitySignatures(::ECS::Entity entity);

		template<typename T>
		::ECS::ComponentType GetComponentType();
		//--------

		static ECSController* Create();
		

	private:
		std::vector<::ECS::Entity>* entities;
		SystemCollection* systems;
	};
}

