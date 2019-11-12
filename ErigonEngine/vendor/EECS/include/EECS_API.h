#pragma once

#include "Core.h"
#include "tools/TypeID.h"

#define ENTITY_TABLE_GROW 1024
#define ENTITY_CHUNK_SIZE 512

#define COMPONENT_TABLE_GROW 1024
#define COMPONENT_CHUNCK_SIZE 512

#define EECS_EVENT_MEMORY_BUFFER_SIZE 4194304
#define EECS_SYSTEM_MEMORY_BUFFER_SIZE 8388608

namespace Erigon
{
	namespace ECS
	{
		class EECSController;
		EECS_API extern EECSController* ECS_Controller;
		EECS_API void Initialize();
		EECS_API void Destroy();

		class MemoryManager;
		extern MemoryManager* ECSMemoryManager;

		class EventHandler;

		class EntityManager;
		class SystemManager;
		class ComponentManager;

		class EECS_API GlobalMemoryUser
		{
		private:
			MemoryManager* ECS_MemoryManager;
		public:
			GlobalMemoryUser();
			virtual ~GlobalMemoryUser();
			inline const void* Allocate(size_t memSize, const char* user = nullptr);
			inline void Free(void* mem);
		};
	}
}