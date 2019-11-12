#pragma once

#include "EECS_API.h"
#include "EECSController.h"
#include "ISystem.h"
#include "memory/allocator/LinearAllocator.h"
#include "tools/TypeID.h"

namespace Erigon
{
	namespace ECS
	{
		using SystemWorkStateMask = std::vector<bool>;

		class EECS_API SystemManager : GlobalMemoryUser
		{
			friend EECSController;

		private:
			using SystemDependencyMatrix = std::vector<std::vector<bool>>;
			using SystemRegistry = std::unordered_map<uint64, ISystem*>;
			using SystemAllocator = LinearAllocator;

			using SystemWorkOrder = std::vector<ISystem*>;

			SystemAllocator* systemAllocator;
			SystemRegistry systems;
			SystemDependencyMatrix systemDependencyMatrix;
			SystemWorkOrder systemWorkOrder;

			SystemManager(const SystemManager&) = delete;
			SystemManager& operator=(SystemManager&) = delete;

			void Update(float32 dt_ms);

		public:

			SystemManager();
			~SystemManager();

			template<class T, class... ARGS>
			T* AddSystem(ARGS&&... args)
			{
				const uint64 systemTypeId = T::SYSTEM_TYPE_ID;

				auto it = this->systems.find(systemTypeId);
				if ((it != this->systems.end() && it->second != nullptr))
				{
					return (T*)it->second;
				}

				T* system = nullptr;
				void* systemMemoryP = this->systemAllocator->Allocate(sizeof(T), alignof(T));
				if (systemMemoryP != nullptr)
				{
					((T*)systemMemoryP)->systemManager = this;
					system = new(systemMemoryP)T(std::forward<ARGS>(args)...);
					this->systems[systemTypeId] = system;
				}

				if (systemTypeId + 1 > this->systemDependencyMatrix.size())
				{
					this->systemDependencyMatrix.resize(systemTypeId + 1);
					for (int index = 0; index < this->systemDependencyMatrix.size(); index++)
					{
						this->systemDependencyMatrix[index].resize(systemTypeId + 1);
					}
				}

				this->systemWorkOrder.push_back(system);
			}

			template<class Sys, class Dep>
			void AddSystemDependency(Sys target, Dep dependency)
			{
				const uint64 TARGET_ID = target->GetSystemTypeID();
				const uint64 DEPENDENCY_ID = dependency->GetSystemTypeID();

				if (this->systemDependencyMatrix[TARGET_ID][DEPENDENCY_ID] != true)
				{
					this->systemDependencyMatrix[TARGET_ID][DEPENDENCY_ID] = true;
				}
			}

			template<class Sys, class Dep, class... Deps>
			void AddSystemDependency(Sys target, Dep dependency, Deps&&... dependencies)
			{
				const uint64 TARGET_ID = target->GetSystemTypeID();
				const uint64 DEPENDENCY_ID = dependency->GetSystemTypeID();

				if (this->systemDependencyMatrix[TARGET_ID][DEPENDENCY_ID] != true)
				{
					this->systemDependencyMatrix[TARGET_ID][DEPENDENCY_ID] = true;
				}
				this->AddSystemDependency(target, std::forward<Deps>(dependencies)...);
			}

			void UpdateSystemWorkOrder();

			template<class T>
			inline T* GetSystem() const
			{
				auto it = this->systems.find(T::SYSTEM_TYPE_ID);
				return it != this->systems.end() ? (T*)it->second : nullptr;
			}

			template<class T>
			void EnableSystem()
			{
				const SystemTypeID systemTypeId = T::SYSTEM_TYPE_ID;

				auto it = this->systems.find(systemTypeId);
				if (it != this->systems.end())
				{
					if (it->second->enabled)
					{
						return;
					}

					it->second->enabled = true;
				}
			}

			template<class T>
			void DisableSystem()
			{
				const SystemTypeID systemTypeId = T::SYSTEM_TYPE_ID;

				auto it = this->systems.find(systemTypeId);
				if (it != this->systems.end())
				{
					if (!it->second->enabled)
					{
						return;
					}

					it->second->enabled = false;
				}
			}

			template<class T>
			void SetSystemUpdateInterval(float32 interval_ms)
			{
				const SystemTypeID systemTypeId = T::SYSTEM_TYPE_ID;

				auto it = this->systems.find(systemTypeId);
				if (it != this->systems.end())
				{
					it->second->updateInterval = interval_ms;
				}
			}

			template<class T>
			void SetSystemPriority(SystemPriority newPriority)
			{
				const SystemTypeID systemTypeId = T::SYSTEM_TYPE_ID;

				auto it = this->systems.find(systemTypeId);
				if (it != this->systems.end())
				{
					SystemPriority oldPrio = it->second->priority;
					if (oldPrio == newPriority)
					{
						return;
					}

					it->second->priority = newPriority;
				}
			}

			SystemWorkStateMask GetSystemWorkState() const;
			void SetSystemWorkState(SystemWorkStateMask mask);

			template<class ... ActiveSystems>
			SystemWorkStateMask GenerateActiveSystemWorkState(ActiveSystems&&... activeSystems)
			{
				SystemWorkStateMask mask(this->systemWorkOrder.size(), false);
				std::list<ISystem*> activeSys = { activeSystems... };
				for (auto sys : activeSys)
				{
					for (int index = 0; index < this->systemWorkOrder.size(); index++)
					{
						if (this->systemWorkOrder[index]->GetSystemTypeID() == sys->GetSystemTypeID())
						{
							mask[index] = true;
							break;
						}
					}
				}
				return mask;
			}
		};
	}
}