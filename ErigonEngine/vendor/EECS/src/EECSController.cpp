#include "EECSController.h"

#include "event/EventHandler.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "tools/Timer.h"

namespace Erigon
{
	namespace ECS
	{
		EECSController::EECSController()
		{
			ecs_timer = new Timer();
			eventHandler = new EventHandler();
			systemManager = new SystemManager();
			componentManager = new ComponentManager();
			entityManager = new EntityManager(this->componentManager);
		}

		EECSController::~EECSController()
		{
			delete ecs_timer;
			ecs_timer = nullptr;

			delete eventHandler;
			eventHandler = nullptr;

			delete systemManager;
			systemManager = nullptr;

			delete componentManager;
			componentManager = nullptr;

			delete entityManager;
			entityManager = nullptr;
		}

		void EECSController::Update(float32 tick_ms)
		{
			ecs_timer->Tick(tick_ms);
			systemManager->Update(tick_ms);
			eventHandler->DispatchEvents();
			entityManager->RemoveDestroyedEntities();
			eventHandler->DispatchEvents();
		}

		void EECSController::UnsubscribeEvent(IEventDelegate* eventDelegate)
		{
			eventHandler->RemoveEventCallback(eventDelegate);
		}
	}
}