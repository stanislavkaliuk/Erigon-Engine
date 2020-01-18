#include "event/IEventListener.h"
#include "EECSController.h"

namespace Erigon
{
	namespace ECS
	{
		IEventListener::IEventListener() {}
		IEventListener::~IEventListener()
		{
			UnregisterAllEventCallback();
		}

		void IEventListener::UnregisterAllEventCallback()
		{
			for (auto cb : this->registeredCallbacks)
			{
				ECS_Controller->UnsubscribeEvent(cb);
			}

			this->registeredCallbacks.clear();
		}
	}
}