#pragma once
#include "Core.h"

namespace Erigon
{
	namespace ECS
	{
		class IEvent;
		using EventDelegateID = size_t;

		class IEventDelegate
		{
		public:

			virtual inline void Invoke(const IEvent* const e) = 0;
			virtual inline EventDelegateID GetDelegateID() const = 0;
			virtual inline int64 GetEventTypeID() const = 0;
			virtual bool operator==(const IEventDelegate* other) const = 0;
			virtual IEventDelegate* Clone() = 0;
		};

		template<class Class, class EventType>
		class EventDelegate : public IEventDelegate
		{
			typedef void(Class::* Callback)(const EventType* const);

			Class* receiver;
			Callback callback;

		public:
			EventDelegate(Class* receiver, Callback& callbackFunc) : receiver(receiver), callback(callbackFunc) {}

			virtual inline void Invoke(const IEvent* const e) override
			{
				(receiver->callback)(reinterpret_cast<const EventType* const>(e));
			}

			virtual inline EventDelegateID GetDelegateID() const override
			{
				static const EventDelegateID delegateID{ typeid(Class).hash_code() ^ typeid(Callback).hash_code() };
				return delegateID;
			}

			virtual inline int64 GetEventTypeID() const override
			{
				return EventType::EVENT_TYPE_ID;
			}

			virtual bool operator==(const IEventDelegate* other) const override
			{
				if (this->GetDelegateID() != other->GetDelegateID())
				{
					return false;
				}

				EventDelegate* eventDelegate = (EventDelegate*)other;
				if (other == nullptr)
				{
					return false;
				}

				return((this->callback == eventDelegate->callback) && (this->receiver == eventDelegate->receiver));
			}

			virtual IEventDelegate* Clone() override
			{
				return new EventDelegate(this->reciver, this->callback);
			}
		};
	}
}