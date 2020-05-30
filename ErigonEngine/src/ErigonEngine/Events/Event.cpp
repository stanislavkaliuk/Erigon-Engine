#include "eepch.h"
#include "Event.h"

namespace ErigonEngine
{
	typedef std::multimap<EventType, const std::function<void(const Event&)>> EventMap;

	static EventMap eventMap;

	void EventManager::AddListener(EventType eventType, const std::function<void(const Event&)>& func)
	{
		eventMap.emplace(eventType, func);
	}

	void EventManager::RemoveListener(EventType eventType, const std::function<void(const Event&)> func)
	{
		typedef EventMap::iterator iterator;
		std::pair<iterator, iterator> iterPair = eventMap.equal_range(eventType);
		iterator it = iterPair.first;
		for (; it != iterPair.second; ++it)
		{
			if (it->second.target_type() == func.target_type())
			{
				eventMap.erase(it);
				break;
			}
		}
	}

	void EventManager::RemoveAllListeners(EventType eventType)
	{
		typedef EventMap::iterator iterator;
		std::pair<iterator, iterator> iterPair = eventMap.equal_range(eventType);
		iterator it = iterPair.first;
		while (it != iterPair.second)
		{
			eventMap.erase(it++);
		}
	}

	void EventManager::InvokeEvent(EventType eventType, Event& event)
	{
		typedef EventMap::iterator iterator;
		std::pair<iterator, iterator> iterPair = eventMap.equal_range(eventType);
		iterator it = iterPair.first;
		for (; it != iterPair.second; it++)
		{
			it->second(event);
		}
	}
}