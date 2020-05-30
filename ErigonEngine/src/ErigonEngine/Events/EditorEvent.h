#pragma once
#include <glm\glm.hpp>
#include "ErigonEngine\Events\Event.h"
namespace ErigonEngine
{
	namespace Editor
	{
		class EditorEvent : public Event
		{
		};

		

		//----- Scene Operation Events -----//

		class SceneViewSizeChangedEvent : public EditorEvent
		{
		public:
			SceneViewSizeChangedEvent(glm::vec2 newSize) : size(newSize) {}
			inline glm::vec2 GetSize() const { return size; }

			EVENT_CLASS_TYPE(SceneViewChanged)
		private:
			glm::vec2 size;
		};

		class SceneCreatedEvent : public EditorEvent
		{
		public:
			SceneCreatedEvent() {}
			EVENT_CLASS_TYPE(SceneCreated)
		};

		class SceneOpenedEvent : public EditorEvent
		{
		public:
			SceneOpenedEvent() {}
			EVENT_CLASS_TYPE(SceneOpened)
		};

		class SceneSavedEvent : public EditorEvent
		{
		public:
			SceneSavedEvent() {}
			EVENT_CLASS_TYPE(SceneSaved)
		};
	}
}