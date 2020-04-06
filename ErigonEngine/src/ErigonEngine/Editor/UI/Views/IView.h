#pragma once
#include <imgui.h>
#include <functional>
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/Events/EditorEvent.h"

namespace ErigonEngine
{
	namespace Editor
	{
		enum class ViewType
		{
			Other,
			SceneView,
			WorldList,
			Inspector
		};

		class IView
		{
		public:
			virtual void Setup(void* controller) = 0;
			virtual void Draw() = 0;
			inline bool IsActive() const { return active; }
			inline bool OnFocus() const { return focused; }
			inline ImVec2 GetSize() const { return size; }
			inline ViewType GetViewType() const { return viewType; }
			inline bool IsResized() const { return resized; }
		protected:
			bool active;
			bool focused;
			ImVec2 size;
			ViewType viewType;
			bool resized;
		};
	}
}