#include "EECS_API.h"
#include "memory/ECSMemory.h"
#include "EECSController.h"

namespace Erigon
{
	namespace ECS
	{
		MemoryManager* ECSMemoryManager = new MemoryManager();

		GlobalMemoryUser::GlobalMemoryUser() : ECS_MemoryManager(ECSMemoryManager) {}
		GlobalMemoryUser::~GlobalMemoryUser() {}

		inline const void* GlobalMemoryUser::Allocate(size_t memSize, const char* user)
		{
			return ECS_MemoryManager->Allocate(memSize, user);
		}

		inline void GlobalMemoryUser::Free(void* memP)
		{
			ECS_MemoryManager->Free(memP);
		}

		EECSController* ECS_Controller = nullptr;

		void Initialize()
		{
			if (ECS_Controller == nullptr)
			{
				ECS_Controller = new EECSController();
			}
		}

		void Destroy()
		{
			if (ECS_Controller != nullptr)
			{
				delete ECS_Controller;
				ECS_Controller = nullptr;
			}

			ECSMemoryManager->CheckMemoryLeaks();
		}
	}
}