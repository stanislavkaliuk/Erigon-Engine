#pragma once
#include "EECSController.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API IEventListener
		{
			using RegisteredCallbacks = std::list<IEventDelegate*>;
			RegisteredCallbacks registeredCallbacks;

		public:
			IEventListener();
			virtual ~IEventListener();

			template<class E, class C>
			inline void RegisterEventCallback(void(C::*Callback)(const E* const))
			{
				IEventDelegate* eventDelegate = new EventDelegate<C, E>(static_cast<C*>(this), Callback);
				registeredCallbacks.push_back(eventDelegate);
				ECS_Controller->SubscribeEvent<E>(eventDelegate);
			}

			template<class E, class C>
			inline void UnregisterEventCallback(void(C::*Callback)(const E* const))
			{
				EventDelegate<C, E> delegate(static_cast<C*>(this), Callback);
				for (auto registeredCallback : this->registeredCallbacks)
				{
					if (registeredCallback->GetDelegateID() == delegate->GetDelegateID())
					{
						this->registeredCallbacks.remove_if([&](const IEventDelegate* other) { return other->operator==(registeredCallback); });
						ECS_Controller->UnsubscribeEvent(&delegate);
						break;
					}
				}
			}

			void UnregisterAllEventCallback();
		};
	}
}