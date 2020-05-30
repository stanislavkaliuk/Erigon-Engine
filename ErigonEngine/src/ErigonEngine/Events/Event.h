#pragma once

#include "ErigonEngine/Core/Core.h"

#include <string>
#include <functional>
#include <vector>

namespace ErigonEngine
{
	enum class EventType
	{
		None = 0,
		// -- Window Events -- //
		WindowClose = 0x0001, 
		WindowResize = 0x0002, 
		WindowFocus = 0x0003, 
		WindowUnFocus = 0x0004, 
		WindowMoved = 0x0005,
		// -- App Events -- //
		AppTick = 0x000A,
		AppUpdate = 0x000B,
		AppRender = 0x000C,
		AppExit = 0x000D,
		// -- Keyboard Events -- //
		KeyPressed = 0x0010,
		KeyReleased = 0x0011,
		KeyTyped = 0x0012,
		// -- Mouse Events -- //
		MouseButtonPressed = 0x001A,
		MouseButtonReleased = 0x001B,
		MouseMoved = 0x001C,
		MouseScrolled = 0x001D,
		// -- Editor Events -- //
		SceneCreated = 0x0020,
		SceneOpened = 0x0021,
		SceneSaved = 0x0022,
		SceneViewChanged = 0x0023
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	class Event
	{
	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(const Event& event) : m_Event(const_cast<Event&>(event))
		{

		}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)& m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	class EventManager
	{
	public:	
		static void AddListener(EventType eventType, const std::function<void(const Event&)>& func);
		static void RemoveListener(EventType eventType, const std::function<void(const Event&)> func);
		static void RemoveAllListeners(EventType eventType);
		static void InvokeEvent(EventType eventType, Event& event);
	};
}
