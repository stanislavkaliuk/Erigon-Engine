#pragma once
#include "EECS_API.h"
#include "event/EventHandler.h"
#include "event/EventDelegate.h"
#include "tools/Timer.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace Erigon
{
	namespace ECS
	{
		class Timer;
		class IEvent;
		class IEventListener;
		class EventHandler;

		class EntityManager;
		class ComponentManager;
		class SystemManager;

		class EECS_API EECSController
		{
			friend class IEntity;
			friend class IComponent;
			friend class ISystem;

			friend class IEvent;
			friend class IEventListener;
			friend class EntityManager;

		private:
			Timer* ecs_timer;
			EntityManager* entityManager;
			ComponentManager* componentManager;
			SystemManager* systemManager;

			EventHandler* eventHandler;

			EECSController(const EECSController&) = delete;
			EECSController& operator=(EECSController&) = delete;

			template<class E>
			inline void SubscribeEvent(IEventDelegate* const eventDelegate)
			{
				eventHandler->AddEventCallback<E>(eventDelegate);
			}

			inline void UnsubscribeEvent(IEventDelegate* eventDelegate);

		public:
			EECSController();
			~EECSController();

			inline EntityManager* GetEntityManager() { return entityManager; }
			inline ComponentManager* GetComponentManager(){ return componentManager; }
			inline SystemManager* GetSystemManager(){ return systemManager; }

			template<class E, class...ARGS>
			void SendEvent(ARGS&&...args)
			{
				eventHandler->Send<E>(std::forward<ARGS>(args)...);
			}

			void Update(float32 tick_ms);
		};
	}
}
