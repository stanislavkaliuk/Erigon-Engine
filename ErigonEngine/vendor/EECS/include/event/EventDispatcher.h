#pragma once
#include "EECS_API.h"
#include "IEventDispatcher.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class EventDispatcher :public IEventDispatcher
		{
			using EventDelegateList = std::list<IEventDelegate*>;
			using PendingRemoveDelegates = std::list<IEventDelegate*>;
			PendingRemoveDelegates pendingRemoveDelegates;
			EventDelegateList eventCallbacks;
			bool isLocked;

		public:
			EventDispatcher() : isLocked(false) {}

			virtual ~EventDispatcher()
			{
				this->pendingRemoveDelegates.clear();
				this->eventCallbacks.clear();
			}

			inline void Dispatch(IEvent* event) override
			{
				this->isLocked = true;
				{
					if (!this->pendingRemoveDelegates.empty())
					{
						for (auto ec : this->pendingRemoveDelegates)
						{
							auto res = std::find_if(this->eventCallbacks.begin(), this->eventCallbacks.end(), [&](const IEventDelegate* other) { return other->operator==(ec); });
							if (res != this->eventCallbacks.end())
							{
								IEventDelegate* ptrMem = (IEventDelegate*)(*res);
								this->eventCallbacks.erase(res);
								delete ptrMem;
								ptrMem = nullptr;
							}
						}
						this->pendingRemoveDelegates.clear();
					}

					for (auto ec : this->eventCallbacks)
					{
						ec->Invoke(event);
					}
				}
				this->isLocked = false;
			}

			virtual void AddEventCallback(IEventDelegate* const eventDelegate) override
			{
				auto res = std::find_if(this->eventCallbacks.begin(), this->eventCallbacks.end(), [&](const IEventDelegate* other) { return other->operator==(eventDelegate); });
				if (res != this->pendingRemoveDelegates.end())
				{
					this->pendingRemoveDelegates.erase(res);
				}

				this->eventCallbacks.push_back(eventDelegate);
			}

			virtual void RemoveEventCallbacks(IEventDelegate* eventDelegate) override
			{
				if (!this->isLocked)
				{
					auto res = std::find_if(this->eventCallbacks.begin(), this->eventCallbacks.end(), [&](const IEventDelegate* other) { return other->operator==(eventDelegate); });
					if (res != this->eventCallbacks.end())
					{
						IEventDelegate* ptrMem = (IEventDelegate*)(*res);
						this->eventCallbacks.erase(res);
						delete ptrMem;
						ptrMem = nullptr;
					}
				}
				else
				{
					auto res = std::find_if(this->eventCallbacks.begin(), this->eventCallbacks.end(), [&](const IEventDelegate* other) { return other->operator==(eventDelegate); });
					this->pendingRemoveDelegates.push_back((*res));
				}
			}

			virtual inline size_t GetEventCallbackCount() const override { return this->eventCallbacks.size(); }
		};
	}
}