#include "event/IEvent.h"
#include "EECSController.h"
#include "tools/Timer.h"

namespace Erigon
{
	namespace ECS
	{
		IEvent::IEvent(EventTypeID typeId) : typeId(typeId)
		{
			this->timeCrated = ECS_Controller->ecs_timer->GetTimeStamp();
		}
	}
}