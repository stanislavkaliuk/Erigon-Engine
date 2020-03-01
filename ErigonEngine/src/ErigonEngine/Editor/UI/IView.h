#pragma once
#include <imgui.h>

namespace ErigonEngine
{
	namespace Editor
	{
		class IView
		{
		public:
			virtual void Setup() = 0;
			virtual void Draw() = 0;
			inline bool IsActive() const { return active; }
			inline bool OnFocus() const { return focused; }
			inline ImVec2 GetSize() const { return size; }
		protected:
			bool active;
			bool focused;
			ImVec2 size;
		};
	}
}