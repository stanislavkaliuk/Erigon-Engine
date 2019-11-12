#include "SystemManager.h"
#include "ISystem.h"

namespace Erigon
{
	namespace ECS
	{
		SystemManager::SystemManager()
		{
			this->systemAllocator = new SystemAllocator(EECS_SYSTEM_MEMORY_BUFFER_SIZE, Allocate(EECS_SYSTEM_MEMORY_BUFFER_SIZE, "SystemManager"));
		}

		SystemManager::~SystemManager()
		{
			for (SystemWorkOrder::reverse_iterator it = this->systemWorkOrder.rbegin(); it != this->systemWorkOrder.rend(); it++)
			{
				(*it)->~ISystem();
				*it = nullptr;
			}

			systemWorkOrder.clear();
			systems.clear();

			Free((void*)this->systemAllocator->GetMemoryZeroAdress());
			delete this->systemAllocator;
			this->systemAllocator = nullptr;
		}

		void SystemManager::Update(float32 dt_ms)
		{
			for (ISystem* system : this->systemWorkOrder)
			{
				system->timeSinceLastUpdate += dt_ms;
				system->needsUpdate = (system->updateInterval < 0.0f) || ((system->updateInterval > 0.0f) && (system->timeSinceLastUpdate > system->updateInterval));
				if (system->enabled && system->needsUpdate)
				{
					system->PreUpdate(dt_ms);
				}
			}

			for (ISystem* system : this->systemWorkOrder)
			{
				if (system->enabled && system->needsUpdate)
				{
					system->Update(dt_ms);
					system->timeSinceLastUpdate = 0.0f;
				}
			}

			for (ISystem* system : this->systemWorkOrder)
			{
				if (system->enabled && system->needsUpdate)
				{
					system->PostUpdate(dt_ms);
				}
			}
		}

		void SystemManager::UpdateSystemWorkOrder()
		{
			static const std::function<void(SystemTypeID, std::vector<int>&, const std::vector<std::vector<bool>>&, std::vector<SystemTypeID>&)> DFS =
				[&](SystemTypeID vertex, std::vector<int>& VERTEX_STATE, const std::vector<std::vector<bool>>& EDGES, std::vector<SystemTypeID>& output)
			{
				VERTEX_STATE[vertex] = 1;
				for (int i = 0; i < VERTEX_STATE.size(); i++)
				{
					if (EDGES[i][vertex] && VERTEX_STATE[i] == 0)
					{
						DFS(i, VERTEX_STATE, EDGES, output);
					}
				}

				VERTEX_STATE[vertex] = 2;
				output.push_back(vertex);
			};

			const size_t NUM_SYSTEMS = this->systemDependencyMatrix.size();

			std::vector<int> INDICIES(NUM_SYSTEMS);
			for (int i = 0; i < NUM_SYSTEMS; i++)
			{
				INDICIES[i] = i;
			}

			std::vector<std::vector<SystemTypeID>> VERTEX_GROUPS;
			std::vector<SystemPriority> GROUP_PRIORITY;

			while (!INDICIES.empty())
			{
				SystemTypeID index = INDICIES.back();
				INDICIES.pop_back();
				if (index == -1)
				{
					continue;
				}

				std::vector<SystemTypeID> group;
				std::vector<SystemTypeID> member;

				SystemPriority groupPriority = LOWER_SYSTEM_PRIORITY;
				member.push_back(index);

				while (!member.empty())
				{
					index = member.back();
					member.pop_back();

					for (int i = 0; i < INDICIES.size(); i++)
					{
						if (INDICIES[i] != -1 && (this->systemDependencyMatrix[i][index] || this->systemDependencyMatrix[index][i]))
						{
							member.push_back(i);
							INDICIES[i] = -1;
						}
					}

					group.push_back(index);

					ISystem* sys = this->systems[index];
					groupPriority = std::max((sys != nullptr ? sys->priority : NORMAL_SYSTEM_PRIORITY), groupPriority);
				}

				VERTEX_GROUPS.push_back(group);
				GROUP_PRIORITY.push_back(groupPriority);
			}

			const size_t NUM_VERTEX_GROUPS = VERTEX_GROUPS.size();

			std::vector<int> vertex_states(NUM_SYSTEMS, 0);
			std::multimap<SystemPriority, std::vector<SystemTypeID>> VERTEX_GROUPS_SORTED;

			for (int i = 0; i < NUM_VERTEX_GROUPS; i++)
			{
				auto gr = VERTEX_GROUPS[i];
				std::vector<SystemTypeID> order;

				for (int i = 0; i < gr.size(); i++)
				{
					if (vertex_states[gr[i]] == 0)
					{
						DFS(gr[i], vertex_states, this->systemDependencyMatrix, order);
					}
				}

				std::reverse(order.begin(), order.end());
				VERTEX_GROUPS_SORTED.insert(std::pair<SystemPriority, std::vector<SystemTypeID>>(std::numeric_limits<SystemPriority>::max() - GROUP_PRIORITY[i], order));
			}

			this->systemWorkOrder.clear();
			for (auto group : VERTEX_GROUPS_SORTED)
			{
				for (auto componentId : group.second)
				{
					ISystem* sys = this->systems[componentId];
					if (sys != nullptr)
					{
						this->systemWorkOrder.push_back(sys);
					}
				}
			}
		}

		SystemWorkStateMask SystemManager::GetSystemWorkState() const
		{
			SystemWorkStateMask mask(this->systemWorkOrder.size());

			for (int i = 0; i < systemWorkOrder.size(); i++)
			{
				mask[i] = this->systemWorkOrder[i]->enabled;
			}

			return mask;
		}

		void SystemManager::SetSystemWorkState(SystemWorkStateMask mask)
		{
			for (int i = 0; i < systemWorkOrder.size(); i++)
			{
				this->systemWorkOrder[i]->enabled = mask[i];
			}
		}
	}
}