#pragma once
#include "EECS_API.h"
namespace Erigon
{
	namespace ECS
	{
		using EventTypeID = typeID;
		using EventTimeStamp = TimeStamp;

		static const EventTypeID INVALID_EVENTTYPE = INVALID_TYPE_ID;

		class EECS_API IEvent
		{
		private:
			EventTypeID typeId;
			EventTimeStamp timeCrated;

		public:
			IEvent(EventTypeID typeId);

			inline const EventTypeID GetEventTypeID() const { return this->typeId; }
			inline const EventTimeStamp GetTimeCreated() const { return this->timeCrated; }
		};
	}
}