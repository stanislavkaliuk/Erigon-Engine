#pragma once
#include "EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class System;

		using SystemTypeID = typeID;
		using SystemPriority = uint16;

		static const SystemTypeID INVALID_SYSTEM_ID = INVALID_TYPE_ID;

		static const SystemPriority LOWEST_SYSTEM_PRIORITY = std::numeric_limits<SystemPriority>::min();
		static const SystemPriority LOWER_SYSTEM_PRIORITY = 99;
		static const SystemPriority LOW_SYSTEM_PRIORITY = 100;
		static const SystemPriority NORMAL_SYSTEM_PRIORITY = 200;
		static const SystemPriority MEDIUM_SYSTEM_PRIORITY = 300;
		static const SystemPriority HIGH_SYSTEM_PRIORITY = 400;
		static const SystemPriority HIGHER_SYSTEM_PRIORITY = 401;
		static const SystemPriority HIGHEST_SYSTEM_PRIORITY = std::numeric_limits<SystemPriority>::max();

		class EECS_API ISystem
		{
			friend class SystemManager;

		private:
			float32 timeSinceLastUpdate;
			SystemPriority priority;
			float32 updateInterval;

			uint8 enabled : 1;
			uint8 needsUpdate : 1;
			uint8 reserved : 6;

		protected:
			ISystem(SystemPriority priority = NORMAL_SYSTEM_PRIORITY, float32 updateInterval_ms = -1.0f);
		public:
			virtual ~ISystem();

			virtual inline const SystemTypeID GetSystemTypeID() const = 0;
			virtual inline const char GetSystemTypeName() const = 0;

			virtual void PreUpdate(float32 deltaTime) = 0;
			virtual void Update(float32 deltaTime) = 0;
			virtual void PostUpdate(float32 deltaTime) = 0;
		};
	}
}